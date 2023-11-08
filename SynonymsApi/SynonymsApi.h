#ifndef _SYNONYMSAPI_
#define _SYNONYMSAPI_ 1
#include <iostream>
#include <string>
#include <stdio.h>
#include <curl/curl.h>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

#define CHUNK_SIZE 2048

typedef struct
{
    unsigned char *buffer;
    size_t len;
    size_t buflen;
} get_request;

// static method to act as a callback for curl
size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    size_t realsize = size * nmemb;
    get_request *req = (get_request *)userdata;

    printf("receive chunk of %zu bytes\n", realsize);

    while (req->buflen < req->len + realsize + 1)
    {
        req->buffer = (unsigned char *)realloc(req->buffer, req->buflen + CHUNK_SIZE);
        req->buflen += CHUNK_SIZE;
    }
    memcpy(&req->buffer[req->len], ptr, realsize);
    req->len += realsize;
    req->buffer[req->len] = 0;

    return realsize;
};

class Synonym
{
public:
    string word;
    vector<string> synonyms;

    Synonym(string word, vector<string> synonyms) : word(word), synonyms(synonyms) {}
};

template <typename T>
class apiGetter
{
private:
    CURL *curl;
    CURLcode res;
    bool isSingleWord(const std::string& word) {
        // Check if a word is a single word (no spaces)
        return word.find(' ') == std::string::npos;
    }

public:

    T *getSynonyms(string word) {
        T *result;

        get_request req = {.buffer = NULL, .len = 0, .buflen = 0};

        curl_global_init(CURL_GLOBAL_ALL);
        curl = curl_easy_init();

        string url = "https://api.api-ninjas.com/v1/thesaurus?word=" + word;

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, (std::string("X-Api-Key: sythbSxxIyOPIjhHjyPKPg==eKE6LYsaBqkodeWc")).c_str());


        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "YourUserAgent");
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); // Set headers
        req.buffer = (unsigned char *)malloc(CHUNK_SIZE);
        req.buflen = CHUNK_SIZE;

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&req);

        res = curl_easy_perform(curl);

        if (res == CURLE_OK) {
            
            json responseData = json::parse(req.buffer);
            // Parse the JSON response and extract synonyms, then store them in the 'result'
            // For example:
            vector<string> synonyms;
            for (auto &synonym : responseData["synonyms"]) {
                string synonymStr = synonym.get<string>();
                
                // Check if the synonym is a single word
                if (isSingleWord(synonymStr)) {
                    synonyms.push_back(synonymStr);
                }
            }
            result = new Synonym(word, synonyms);
            free(req.buffer);
        } else {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);
        curl_global_cleanup();
        
        return result;
    }
};
#endif

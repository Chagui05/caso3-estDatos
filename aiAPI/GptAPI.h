#ifndef _GPT_
#define _GPT_ 1
#include <iostream>
#include <string>
#include <stdio.h>
#include <curl/curl.h>
#include "../generic/json.hpp"
//g++ -o gpt.o GptAPI.cpp -lcurl

using namespace std;
using json = nlohmann::json;

#define CHUNK_SIZE 2048

template <typename T>
class GptAPI
{
private:
    CURL *curl;
    CURLcode res;
    string apiKey;

public:
    GptAPI()
    {
    }
    GptAPI(string apiKey)
    {
        this->apiKey = apiKey;
    }
    T* askQuestion(string &question, string &model)
    {
        cout << "GPT3 API" << endl;
        T* result;
        get_request req = {.buffer = NULL, .len = 0, .buflen = 0};

        curl_global_init(CURL_GLOBAL_ALL);
        curl = curl_easy_init();

        // build the URL with the proper entryid
        string url = "https://api.openai.com/v1/chat/completions";
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, ("Authorization: Bearer " + apiKey).c_str());
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/93.0.4577.63 Safari/537.36");
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

        //request prompt
        cout << "payload" << endl;
        json payload = {
        {"model", model},
        {"messages", json::array({ // Ensure "messages" is an array
            {{"role", "user"}, {"content", question}}
        })}
    };
            
        cout << payload.dump() << endl;
        // Convert the JSON payload to a string
        std::string payloadStr = payload.dump();

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payloadStr.c_str());

        // prepare the callback function to catch the result json
        req.buffer = (unsigned char *)malloc(CHUNK_SIZE);
        req.buflen = CHUNK_SIZE;

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&req);

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);

        /* Check for errors */
        if (res == CURLE_OK )
        {
            cout<<"call success"<<endl;
            json responseData = json::parse(req.buffer);
            cout<<"parsed: "<<responseData.dump()<<endl;
            result = new string(responseData["choices"][0]["message"]["content"].get<string>());
            cout<<"assigned: "<<*result<<endl;
            free(req.buffer);
            cout<<"freed"<<endl;
        }
        else
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            if (req.buffer != nullptr)
            {
                json errorData = json::parse(req.buffer);
                cout << "API Error: " << errorData["error"]["message"] << endl;
                free(req.buffer);
            }
        }

        // clean the curl objects
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        cout <<"API response: "<< *result << endl;
        return result;
    };
};

//int main(void)
// {
//     string* response = new string();
//     string question = "What is true love? can you experience it?";

//     string chatGpt = "gpt-3.5-turbo";//model type
//     GptAPI<string> gpt = GptAPI<string>("ApiKeyHere");

//     response = gpt.askQuestion(question, chatGpt);
//     cout <<"API response: "<< *response << endl;
//     return 0;
// }

#endif
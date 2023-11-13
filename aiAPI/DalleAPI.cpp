#include <iostream>
#include <string>
#include <curl/curl.h>

class DalleAPI {
public:
    DalleAPI(const std::string& apiKey) : apiKey(apiKey), curl(nullptr) {
        // Initialize cURL
        if (curl_global_init(CURL_GLOBAL_DEFAULT) != CURLE_OK) {
            std::cerr << "Error initializing cURL." << std::endl;
        } else {
            curl = curl_easy_init();

            // Set common cURL options
            if (curl) {
                curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &DalleAPI::WriteCallback);
            } else {
                std::cerr << "Error initializing cURL handle." << std::endl;
            }
        }
    }

    ~DalleAPI() {
        // Cleanup cURL
        if (curl) {
            curl_easy_cleanup(curl);
        }
        curl_global_cleanup();
    }

    std::string generateImage(const std::string& prompt) {
        if (!curl) {
            std::cerr << "Error initializing cURL." << std::endl;
            return "";
        }

        // DALL-E API endpoint
        std::string apiUrl = "https://api.openai.com/v1/dalle-generate"; // Check OpenAI's documentation for the correct endpoint

        // Prepare headers
        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, ("Authorization: Bearer " + apiKey).c_str());
        headers = curl_slist_append(headers, "Content-Type: application/json");

        // Prepare JSON data
        std::string jsonData = "{\"prompt\": \"" + prompt + "\"}";

        // Set cURL options
        curl_easy_setopt(curl, CURLOPT_URL, apiUrl.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());

        // Response data
        std::string responseData;

        // Perform the HTTP POST request
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "cURL failed: " << curl_easy_strerror(res) << std::endl;
        }

        // Cleanup
        curl_slist_free_all(headers);

        return responseData;
    }

private:
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
        size_t totalSize = size * nmemb;
        output->append(static_cast<char*>(contents), totalSize);
        return totalSize;
    }

    CURL* curl;
    std::string apiKey;
};

int main() {
    // Replace 'YOUR_DALLE_API_KEY' with your actual DALL-E API key
    std::string apiKey = "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";
    DalleAPI dalle(apiKey);

    // Replace 'Your prompt here...' with your actual prompt
    std::string prompt = "a very cute cat";
    std::string imageData = dalle.generateImage(prompt);

    // Handle the imageData as needed, e.g., save it to a file or display it
    std::cout << "Received image data:\n" << imageData << std::endl;

    return 0;
}

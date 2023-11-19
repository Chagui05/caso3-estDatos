#ifndef _RESTSERVICE_
#define _RESTSERVICE_ 1

#include "httplib.h"
#include <iostream>
#include <string>

std::string recievedPhrase;

std::string formatPhrasePost(const std::string& input) {
    // Find the position of the "phrase" key
    size_t phrasePos = input.find("phrase");

    // Check if the "phrase" key is found
    if (phrasePos != std::string::npos) {
        // Find the position of the colon after the "phrase" key
        size_t colonPos = input.find(':', phrasePos);

        // Find the position of the opening quote after the colon
        size_t quotePos = input.find('"', colonPos + 1);

        // Find the position of the closing quote after the opening quote
        size_t endQuotePos = input.find('"', quotePos + 1);

        // Extract the substring between the opening and closing quotes
        return input.substr(quotePos + 1, endQuotePos - quotePos - 1);
    } else {
        return "Invalid input format";
    }
}

std::string handle_post(const httplib::Request& req, httplib::Response& res) {
    res.set_content("Hola", "text/plain");
    std::cout << req.body << std::endl;
    recievedPhrase=req.body;
    std::cout << "Frase Recibida: " << formatPhrasePost(recievedPhrase) <<std::endl;
    return formatPhrasePost(recievedPhrase);
}

std::string startServer(){
    httplib::Server svr;
    svr.Options("/", [](const auto& req, auto& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Headers", "*");
        res.set_header("Allow", "GET, POST, HEAD, OPTIONS");
    });

    // Handle POST requests to / endpoint
    svr.Post("/", [](const httplib::Request& req, httplib::Response& res) {
        handle_post(req, res);
    });
    
    std::cout << "Server listening on http://localhost:8080" << std::endl;

    svr.listen("0.0.0.0", 8080);
    return recievedPhrase;
}

int main(){
    startServer();
    return 0;
}

#endif


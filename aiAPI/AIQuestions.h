#ifndef _AIQUEST_
#define _AIQUEST_ 1
#include <iostream>
#include <string>
#include <stdio.h>
#include <curl/curl.h>
#include "../generic/json.hpp"
#include "DalleAPI.h"
#include "GptAPI.h"


class AIQuestions
{
private:
    DalleAPI<string> dalleAPI;
    GptAPI<string> gptAPI;
    string apiKey;

public:


    AIQuestions(string apiKey)
    {
        this->apiKey = apiKey;
        dalleAPI = DalleAPI<string>(apiKey);
        gptAPI = GptAPI<string>(apiKey);
    }

    string* askQuestion(string &question)
    {
        string* result = new string();
        string model = "gpt-3.5-turbo";
        result = gptAPI.askQuestion(question,model);
        return result;
    }

    string* genImage(string &input)
    {
        string* result = new string();
        string model = "dall-e-3";
        result = dalleAPI.genImage(input, model);
        return result;
    }
};
#endif
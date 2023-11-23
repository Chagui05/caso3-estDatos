#include <iostream>
#include "SentimentApi.h"


int main(){
    ApiGetter api;
    // Palabra para la que deseas obtener el sentimiento
    string wordToAnalyze = "magic";
    string sentiment = api.getSentimentString(wordToAnalyze);

    std::cout<<"Sentimiento de "<<wordToAnalyze<<": "<<sentiment<<std::endl;
    
    return 0;
}
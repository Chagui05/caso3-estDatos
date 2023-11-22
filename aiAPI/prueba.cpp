#ifndef _PRUEBA_
#define _PRUEBA_ 1
#include <iostream>
#include <string>
#include <stdio.h>
#include "AIQuestions.h"
using namespace std;

int main()
{
    AIQuestions asker = AIQuestions("APIHERE");

    string question = "What is the meaning of life?";
    string imgPrompt = "A painting of a cat sitting on a chair";
    string* res = asker.askQuestion(question);
    string* img = asker.genImage(imgPrompt);

    cout <<"Respuesta: "<< *res << endl;
    cout <<"Imagen: "<< *img << endl;
}

#endif
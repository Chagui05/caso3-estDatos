#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
#include "BookHasher.h"
#include "BookParragraphFinder.h"
#include "FullProgram.h"
#include "../phraseDecomposer/PhraseDecomposer.h"
using namespace std;

int main()
{
  //g++ -o prueba.o main.cpp -lcurl
  FullProgram program = FullProgram();

  program.createBooks("../bookDatabase");

  program.run("magic");

  program.run("hello magic ");

  program.run("Much to the author’s surprise, and (if he may say so without additional offence) considerably to his amusement, he finds that his sketch of official life, introductory to THE SCARLET LETTER, has created an unprecedented excitement in the respectable community immediately around him. It could hardly have been more violent, indeed, had he burned down the Custom-House, and quenched its lastsmoking ember in the blood of a certain venerable");

  program.run("magic");

  return 0;
};
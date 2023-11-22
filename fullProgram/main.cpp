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
  FullProgram program = FullProgram();

  program.createBooks("../bookDatabase");

  program.run("The quick brown fox jumps over the lazy dog");

  return 0;
};
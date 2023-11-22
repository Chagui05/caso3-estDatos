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

  program.run("bosom those spacious coves indent eastern shore Hudson broad expansion river denominated ancient Dutch navigators prudently");

  return 0;
};
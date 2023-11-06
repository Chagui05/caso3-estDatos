#include "PhraseBookSearcher.h"
#include "PhraseDecomposer.h"

int main() {
    string phrase = "musketeers alexandre fourth hello magic attempt";
    PhraseDecomposer decomposer = PhraseDecomposer();
    PhraseBookSearcher phraseBookSearcher = PhraseBookSearcher(decomposer, phrase);
    phraseBookSearcher.search();
    
    
    return 0;
}   
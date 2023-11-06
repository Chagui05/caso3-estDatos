#include "PhraseBookSearcher.h"
#include "PhraseDecomposer.h"

int main() {
    string phrase = "the save three musketeers save the day";
    PhraseDecomposer decomposer = PhraseDecomposer();
    PhraseBookSearcher phraseBookSearcher = PhraseBookSearcher(decomposer, phrase);
    phraseBookSearcher.search();
    
    
    return 0;
}   
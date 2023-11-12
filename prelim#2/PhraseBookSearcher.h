#ifndef PHRASEBOOKSEARCHER_H
#define PHRASEBOOKSEARCHER_H

#include <vector>
#include <string>
#include "PhraseDecomposer.h"
#include "../indexacion/BookHasher.h"
#include "../SynonymsApi/SynonymsApi.h"
using namespace std;

class PhraseBookSearcher {
private:
    PhraseDecomposer& decomposer;
    string& phrase;
    int numPalabras;
    vector<string> palabras;
    BookHasher bookHasher;
public:
    // Constructor that takes a PhraseDecomposer object as a parameter
    PhraseBookSearcher(PhraseDecomposer& decomposer,  string& phrase)
        : decomposer(decomposer), phrase(phrase), numPalabras(0), bookHasher() {
        this->palabras = getWordAndSynonyms(getWords(decomposer.removeStopwords(phrase)));
        this->numPalabras = this->palabras.size();
        bookHasher.hashBooksInFolder("../bookDatabase");
    }
    
    void search() {
        cout <<endl<<endl;
        cout << "PHRASE: " << decomposer.removeStopwords(phrase)<<endl;
        cout << "RANK THE BOOKS BY THESE WORDS: "; for(string s: palabras){ cout << s << endl; }
        cout <<endl<<endl;

        // bookHasher.getMultiSetAVL(palabras);

        // cout <<endl<<endl;
        // cout << "BOOKS RANKED" << endl;
        // int num = 10;
        // cout << "Top: " << num << endl;

        // bookHasher.setTopAmountBooks(num);

        // bookHasher.getLibrary()->printTopBooks();
    }

    void printWords(){
        for (const string& word : palabras) {
            std::cout <<"Palabra: "<< word << std::endl;
        }
    }
    vector<string> getWords(const std::string input) {
    vector<string> words;
    istringstream iss(input);
    string word;

    while (iss >> word) {
        // Remove non-alphabetic characters from the word
        word.erase(remove_if(word.begin(), word.end(), [](char c) { return !isalpha(c); }), word.end());

        // Convert the word to lowercase for case-insensitive comparison
        transform(word.begin(), word.end(), word.begin(), ::tolower);

        words.push_back(word);
    }

    return words;
    }

        // Function to get synonyms for a vector of words
    std::vector<std::string> getWordAndSynonyms(const std::vector<std::string>& words) {
        apiGetter<Synonym> api; // Assuming Synonym is the class to store synonyms
        std::vector<std::string> result;

        for (const std::string& word : words) {
            Synonym *synonyms = api.getSynonyms(word);

            if (synonyms) {
                // Add the original word to the result if it's not already in there
                if (std::find(result.begin(), result.end(), word) == result.end()) {
                    result.push_back(word);
                }

                // Add synonyms to the result
                for (const std::string& synonym : synonyms->synonyms) {
                    // Only add the synonym if it's not already in the result
                    if (std::find(result.begin(), result.end(), synonym) == result.end()) {
                        result.push_back(synonym);
                    }
                }

                delete synonyms; // Clean up the Synonym object
            }
        }

        return result;
    }
};

#endif

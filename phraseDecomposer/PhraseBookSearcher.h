#ifndef PHRASEBOOKSEARCHER_H
#define PHRASEBOOKSEARCHER_H

#include <vector>
#include <string>
#include "PhraseDecomposer.h"
#include "../indexacion/BookHasher.h"
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
        this->palabras = getWords(decomposer.removeStopwords(phrase));
        this->numPalabras = this->palabras.size();
        bookHasher.hashBooksInFolder("../bookDatabase");
    }
    
    void search() {
        cout <<endl<<endl;
        cout << "RANK THE BOOKS BY THIS WORD: "; for(string s: palabras){ cout << s << " "; }
        cout <<endl<<endl;

        bookHasher.getMultiSetAVL(palabras);

        cout <<endl<<endl;
        cout << "BOOKS RANKED" << endl;
        int num = 10;
        cout << "Top: " << num << endl;

        bookHasher.setTopAmountBooks(num);

        bookHasher.getLibrary()->printTopBooks();
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
};

#endif

#ifndef _PHRASEDECOMPOSER_
#define _PHRASEDECOMPOSER_ 1

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "../SynonymsApi/SynonymsApi.h"

// Clase que se encarga de eliminar las palabras de parada de un texto
using namespace std;
class PhraseDecomposer {
public:
    PhraseDecomposer() {
    }

    string removeStopwords(const string& input) {
        string result;
        istringstream iss(input);
        string word;
        vector<string> stopWords = loadStopwords();

        while (iss >> word) {
            // Remove non-alphabetic characters from the word
            word.erase(remove_if(word.begin(), word.end(), [](char c) { return !isalpha(c); }), word.end());

            // Convert the word to lowercase for case-insensitive comparison
            transform(word.begin(), word.end(), word.begin(), ::tolower);

            // Assume the word is not a stopword
            bool isStopword = false;

            // If the word is in the list of stopwords, mark it as a stopword
            for (const string& stopWord : stopWords) {
                if (word.compare(stopWord) == 0) {
                    isStopword = true;
                    break;
                }
            }

            // If the word is not a stopword, add it to the result
            if (!isStopword) {
                result += word + " ";
            }
        }

        // Remove the trailing space if necessary
        if (!result.empty()) {
            result.pop_back();
        }

        return result;
    }

    vector<string> getWords(const string& input) {
        string removedStopWords = removeStopwords(input);
        vector<string> words;
        istringstream iss(removedStopWords);
        string word;

        while (iss >> word) {
            // Remove non-alphabetic characters from the word
            word.erase(remove_if(word.begin(), word.end(), [](char c) { return !isalpha(c); }), word.end());

            // Convert the word to lowercase for case-insensitive comparison
            transform(word.begin(), word.end(), word.begin(), ::tolower);

            if(word.size() > 4)
            {
                words.push_back(word);
            }
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
        vector<std::string> reducedResult;
        for(int i = 0 ; i < 15; i++)//solo 15 palabras, se puede cambiar valor alambrado
        {
            reducedResult.push_back(result[i]);
        }

        return reducedResult;
    }

private:
    vector<string> stopwords;

    vector<string> loadStopwords() {
        // Definir las palabras de parada en minúsculas directamente aquí
        vector<string> stopwords = {
    "a", "about", "above", "across", "after", "again", "against", "all", "almost", "alone", 
    "along", "already", "also", "although", "always", "among", "an", "and", "another", "any", 
    "anybody", "anyone", "anything", "anywhere", "are", "area", "areas", "around", "as", "ask", 
    "asked", "asking", "asks", "at", "away", "b", "back", "backed", "backing", "backs", "be", 
    "became", "because", "become", "becomes", "been", "before", "began", "behind", "being", 
    "beings", "best", "better", "between", "big", "both", "but", "by", "c", "came", "can", 
    "cannot", "case", "cases", "certain", "certainly", "clear", "clearly", "come", "could", 
    "d", "did", "differ", "different", "differently", "do", "does", "done", "down", "downed", 
    "downing", "downs", "during", "e", "each", "early", "either", "end", "ended", "ending", 
    "ends", "enough", "even", "evenly", "ever", "every", "everybody", "everyone", "everything", 
    "everywhere", "f", "face", "faces", "fact", "facts", "far", "felt", "few", "find", "finds", 
    "first", "for", "four", "from", "full", "fully", "further", "furthered", "furthering", 
    "furthers", "g", "gave", "general", "generally", "get", "gets", "give", "given", "gives", 
    "go", "going", "good", "goods", "got", "great", "greater", "greatest", "group", "grouped", 
    "grouping", "groups", "h", "had", "has", "have", "having", "he", "her", "here", "herself", 
    "high", "higher", "highest", "him", "himself", "his", "how", "however", "i", "if", 
    "important", "in", "interest", "interested", "interesting", "interests", "into", "is", 
    "it", "its", "itself", "j", "just", "k", "keep", "keeps", "kind", "knew", "know", "known", 
    "knows", "l", "large", "last", "later", "latest", "least", "less", "let", "lets", "like", 
    "likely", "long", "longer", "m", "made", "make", "making", "man", "many", "may", "me", 
    "member", "members", "men", "might", "more", "most", "mostly", "mr", "mrs", "much", "must", 
    "my", "myself", "n", "necessary", "need", "needed", "needing", "needs", "never", "new", 
    "next", "no", "nobody", "non", "noone", "not", "nothing", "now", "nowhere", "number", 
    "o", "of", "off", "often", "old", "once", "one", "only", "open", "or", "order", "other", 
    "others", "our", "out", "over", "p", "part", "parts", "per", "perhaps", "place", "point", 
    "possible", "present", "problems", "put", "puts", "q", "quite", "r", "rather", "really", 
    "right", "room", "rooms", "s", "said", "same", "saw", "say", "says", "second", "see", 
    "seem", "seemed", "seeming", "seems", "several", "shall", "she", "should", "show", "shows", 
    "side", "sides", "since", "small", "so", "some", "something", "state", "still", "such", 
    "sure", "t", "take", "taken", "than", "that", "the", "their", "them", "then", "there", 
    "therefore", "these", "they", "thing", "things", "think", "this", "those", "though", 
    "thought", "three", "through", "thus", "to", "today", "together", "too", "toward", 
    "turn", "turned", "turning", "turns", "two", "u", "under", "until", "up", "upon", "us", 
    "use", "used", "uses", "v", "very", "w", "want", "wanted", "wanting", "wants", "was", 
    "way", "ways", "well", "went", "were", "what", "when", "where", "whether", "which", 
    "while", "who", "whose", "why", "will", "with", "within", "without", "work", "worked", 
    "working", "works", "would", "x", "y", "year", "years", "yet", "you", "your", "yours", "z"
};

        cout << "Palabras de parada cargadas: ";
        for (const string& word : stopwords) {
        }
        cout << endl;
        return stopwords;
    }
};

#endif
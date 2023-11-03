#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

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

int main() {
    PhraseDecomposer decomposer;
    std::string inputText = "This is a sample text with some stopwords in it.";
    std::string result = decomposer.removeStopwords(inputText);
    std::cout << "Texto original: " << inputText << std::endl;
    std::cout << "Texto sin stopwords: " << result << std::endl;
    std::cout << "Palabras del texto sin stopwords: "<<std::endl;;
    for (const string& word : decomposer.getWords(result)) {
        std::cout <<"Palabra: "<< word << std::endl;
    }

    return 0;
}

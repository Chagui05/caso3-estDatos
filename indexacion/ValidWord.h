#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
using namespace std;

class ValidWord
{
private:
    string word;
    int count;

public:
    ValidWord()
    {
        word = "";
        count = 0;
    }
    ValidWord(string word, int count)
    {
        this->word = word;
        this->count = count;
    }

    string getWord()
    {
        return word;
    }

    int getCount()
    {
        return count;
    }

    void setWord(string word)
    {
        this->word = word;
    }

    void setCount(int count)
    {
        this->count = count;
    }

    bool operator==(const ValidWord &other) const {
        return word == other.word;
    }
    struct Hash {
        std::size_t operator()(const ValidWord& k) const {
            return std::hash<std::string>()(k.word);
        }
    };

};
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
#include "ValidWord.h"
using namespace std;

class Book
{
private:
    unordered_map<ValidWord, vector<int>> wordIndex;
    string title;
    string description;
    string author;

public:
    Book(string title, string description, string author)
    {
        this->title = title;
        this->description = description;
        this->author = author;
    }

    void loadBook(string &filePath)
    {
        ifstream file(filePath);

        if (!file)
        {
            cout << "Error al abrir el archivo: " << filePath << std::endl;
            return;
        }

        string line;
        getline(file, line);
        title = line.substr(10);

        getline(file, line);
        getline(file, line);
        description = line.substr(13);

        getline(file, line);
        getline(file, line);
        author = line.substr(8);
        file.close();
    }

    void indexContent(string &filePath)
    {
        ifstream file(filePath);
        string word;
        ValidWord validWord;

        int position = 0;

        if (!file)
        {
            cout << "Error al abrir el archivo: " << filePath << std::endl;
            return;
        }

        while (file >> word)
        {
            validWord.setWord(word);
            if (word.length() > 4 && wordIndex.find(validWord) == wordIndex.end())
            {
                wordIndex[validWord].push_back(position);
            }
            else if (word.length() > 4 && wordIndex.find(validWord) != wordIndex.end())
            {
                wordIndex[validWord].push_back(position);
            }
            position++;
        }
    }

    string getTitle()
    {
        return title;
    }
    string getDescription()
    {
        return description;
    }
    string getAuthor()
    {
        return author;
    }

    unordered_map<ValidWord, vector<int>> getWordIndex()
    {
        return wordIndex;
    }

    void setWordIndex(unordered_map<ValidWord, vector<int>> wordIndex)
    {
        this->wordIndex = wordIndex;
    }
};
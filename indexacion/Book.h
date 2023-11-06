#ifndef _BOOK_
#define _BOOK_ 1
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
using namespace std;
void toLowerCase(string& str);

class Book
{
private:
    unordered_map<string, vector<int>> wordIndex;
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
    
    void buildBook(string &filePath)
    {
        loadBook(filePath);
        indexContent(filePath);
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

        int position = 0;

        if (!file)
        {
            cout << "Error al abrir el archivo: " << filePath << std::endl;
            return;
        }

        while (file >> word)
        {
            if (word.length() > 4)
            {
                toLowerCase(word);
                wordIndex[word].push_back(position);
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

    unordered_map<string, vector<int>> getWordIndex()
    {
        return wordIndex;
    }

    void setWordIndex(unordered_map<string, vector<int>> wordIndex)
    {
        this->wordIndex = wordIndex;
    }

    void printWordIndex()
    {
        for (const auto &pair : wordIndex)
        {
            std::cout <<"reps: " << pair.second.size() << " " << pair.first << ": ";
            for (int pos : pair.second)
            {
                std::cout << pos << " ";
            }
            std::cout << std::endl;
        }
    }
};
void toLowerCase(string& str) {
    for (char& c : str) {
        c = tolower(c);
    }
}

#endif
#ifndef _BOOK_
#define _BOOK_ 1
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include "../prelim#2/Parragraph.h"
#include "../generic/ImplementedBtree.h"
#include "../generic/MultiAVLImplementation.h"
using namespace std;
void toLowerCase(string &str);
bool isLineEmptyOrWhitespace(const std::string& line);
class Book
{
private:
    unordered_map<string, vector<int>> wordIndex; // for word indexing
    BTree WordParragraphBTree;                    // for paragraph indexing
    string title;
    string description;
    string author;
    string filePath;
    MultisetAVLTree<Parragraph> allParragraphsRanked;
    vector<Parragraph> top3Parragraphs;
    vector<string> wordMatches;

public:
    Book() {}
    Book(string title, string description, string author)
    {
        this->title = title;
        this->description = description;
        this->author = author;
        WordParragraphBTree = BTree(3);
    }

    void buildBook(string &filePath)
    {
        loadBook(filePath);
        indexContent(filePath);
        cout<<"Book partially built ";
        loadBtree(filePath);
        cout<<"Book built"<<endl;
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

    void loadBtree(string &filePath)
    {
        cout<<" ,Loading btree"<<endl;
        ifstream file(filePath);

        if (!file)
        {
            cout << "Error al abrir el archivo: " << filePath << std::endl;
            return;
        }
        string parragraph;
        string line;
        int page = 1;
        int lineCount = 1;
        int generalLineCount = 1;

        while (getline(file, line))
        {
            if (!isLineEmptyOrWhitespace(line))
            {
                line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
                line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
                parragraph += " "+line;
            }

            if (lineCount == 5) // for a parragraph
            {
                // cout << parragraph << endl<< endl;
                loadBtreeHelper(parragraph, page);
                lineCount = 0;
                parragraph = "";
            }

            lineCount++;
            generalLineCount++;

            if (generalLineCount == 40) // for a page
            {
                page++;
                generalLineCount = 1;
            }
        }
        file.close(); //// probar eso
    }

    void loadBtreeHelper(string pParra, int page) // this will look up the words in the parragraph and add them to the btree
    {
        istringstream parragraph(pParra);
        string word;
        while (parragraph >> word)
        {
            // Remove non-letter characters from the string//taken from chatgpt, just this part
            word.erase(std::remove_if(word.begin(), word.end(), [](char c)
                                          { return !std::isalpha(c); }),
                           word.end());
            toLowerCase(word);
            Word wordObj;
            wordObj.key = word;
            wordObj.pages.push_back(page);
            wordObj.description.push_back(pParra);
            if (wordObj.key != "" || wordObj.key != " " || wordObj.key.length() > 4)
            {
                WordParragraphBTree.insert(wordObj);
            }
        }
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
                word.erase(std::remove_if(word.begin(), word.end(), [](char c)
                                          { return !std::isalpha(c); }),
                           word.end());
                wordIndex[word].push_back(position);
            }
            position++;
        }
        file.close(); //// probar eso
    }

    void printWordIndex()
    {
        for (const auto &pair : wordIndex)
        {
            std::cout << "reps: " << pair.second.size() << " " << pair.first << ": ";
            for (int pos : pair.second)
            {
                std::cout << pos << " ";
            }
            std::cout << std::endl;
        }
    }

    void addWordMatch(string word)
    {
        wordMatches.push_back(word);
    }

    void addToMultiSetAVL(Parragraph parragraph)
    {
        allParragraphsRanked.insert(&parragraph, parragraph.getRating());
    }
    MultisetAVLTree<Parragraph> getAllParragraphsRanked()
    {
        return allParragraphsRanked;
    }
    BTree getBtree()
    {
        return WordParragraphBTree;
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
    string getFilePath()
    {
        return filePath;
    }
    unordered_map<string, vector<int>> getWordIndex()
    {
        return wordIndex;
    }
    void setWordIndex(unordered_map<string, vector<int>> wordIndex)
    {
        this->wordIndex = wordIndex;
    }
    vector<string> getWordMatches()
    {
        return wordMatches;
    }
};



bool isLineEmptyOrWhitespace(const std::string& line) {
    return line.empty() || std::all_of(line.begin(), line.end(), [](unsigned char c) { return std::isspace(c); });
}
void toLowerCase(string &str)
{
    for (char &c : str)
    {
        c = tolower(c);
    }
}

#endif
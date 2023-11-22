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
    BTree* WordParragraphBTree;                    // for paragraph indexing
    string title;
    string description;
    string author;
    string filePath;
    MultisetAVLTree<Parragraph>* allParragraphsRanked;
    vector<Parragraph> top3Parragraphs;
    vector<string> wordMatches;

public:
    Book() 
    {
        allParragraphsRanked = new MultisetAVLTree<Parragraph>();
    }
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
        cout<<"Book partially built ";
        loadBtree(filePath);
        cout<<"Book built"<<endl;
        setFilePath(filePath);
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
        getline(file, line);//TODO: quitar el /r, la funcion debe estar abajo
        title = line;

        getline(file, line);
        getline(file, line);
        description = line;

        getline(file, line);
        getline(file, line);
        author = line;
        file.close();
    }

    void loadBtree(string &filePath)
    {
        WordParragraphBTree = new BTree(3);
        cout<<" ,Loading btree"<<endl;
        ifstream file(filePath);

        if (!file)
        {
            cout << "Error al abrir el archivo: " << filePath << std::endl;
            return;
        }
        string *parragraph = new string();
        string* line = new string();
        string *space = new string(" ");
        int *page = new int(1);
        int *lineCount = new int(1);
        int *generalLineCount = new int(1);

        while (getline(file, *line)) 
        {
            if (!isLineEmptyOrWhitespace(*line))
            {
                line->erase(std::remove(line->begin(), line->end(), '\n'), line->end());
                line->erase(std::remove(line->begin(), line->end(), '\r'), line->end());
                *parragraph += *space+*line;
            }

            if (*lineCount == 5) // for a parragraph
            {
                
                loadBtreeHelper(parragraph, page);
                *lineCount = 0;
                delete parragraph; 
                parragraph = new string();
            }

            (*lineCount)++;
            (*generalLineCount)++;

            if (*generalLineCount == 40) // for a page
            {
                (*page)++;
                delete generalLineCount; 
                generalLineCount = new int(1);
            }
        }
        delete parragraph;
        delete line;
        delete space;
        file.close(); //// probar eso
        cout<<"btree loaded"<<endl;
    }

    void loadBtreeHelper(string *pParra, int *page) // this will look up the words in the parragraph and add them to the btree
    {
        istringstream parragraph(*pParra);
        string word;
        while (parragraph >> word)
        {
            // Remove non-letter characters from the string//taken from chatgpt, just this part
            word.erase(std::remove_if(word.begin(), word.end(), [](char c)
                                          { return !std::isalpha(c); }),
                           word.end());
            toLowerCase(word);
            Word* wordObj = new Word();
            wordObj->key = new string(word);
            wordObj->pages->push_back(new int(*page));  // Create a new integer, not just a pointer
            wordObj->description->push_back(new string(*pParra));  // Create a new string, not just a pointer
            if (word.length() > 4)
            {
                WordParragraphBTree->insert(wordObj);// TODO: revisar que si se este metiendo info valida
            }
            delete wordObj;
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

    void printBTree()
    {
        WordParragraphBTree->traverse();
    }

    void addWordMatch(string word)
    {
        wordMatches.push_back(word);
    }

    void addToMultiSetAVL(Parragraph *parragraph)
    {
        Parragraph *parra = new Parragraph(*parragraph);
        allParragraphsRanked->insert(parra, parra->getRating());
    }

    MultisetAVLTree<Parragraph>* getAllParragraphsRanked()
    {
        return allParragraphsRanked;
    }
    BTree* getBtree()
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
    void setFilePath(string filePath)
    {
        this->filePath = filePath;
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
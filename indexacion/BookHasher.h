#ifndef _BOOKHASHER_
#define _BOOKHASHER_ 1
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
#include <filesystem>
#include "Library.h"
#include "../generic/MultiAVLImplementation.h"
using namespace std;
namespace fs = std::filesystem;

class BookHasher
{
private:
    Library books;
    MultisetAVLTree<Book> rankedBooks;

public:
    BookHasher(){};

    void hashBooksInFolder(const string &folderPath)
    {
        for (const auto &file : fs::directory_iterator(folderPath))
        {
            string path = file.path();
            Book book = Book("", "", "");
            book.buildBook(path);
            cout << path << endl;
            books.addToBooks(book);
        }
    };

    void getMultiSetAVL(vector<string> search)
    {
        vector<Book>* allBooks = books.getBooks();
        rankedBooks = MultisetAVLTree<Book>();

        for (int i = 0; i < allBooks->size(); i++)
        {
            unordered_map<string, vector<int>> wordIndex = allBooks->at(i).getWordIndex();
            int appearances = 0;
            for (string s : search)
            {
                if (wordIndex.find(s) != wordIndex.end())
                {
                    string title = allBooks->at(i).getTitle();
                    cout << "Se encontró " << s << " en: "<<title << endl;
                    cout<<"Apariciones: "<<wordIndex[s].size()<<endl;
                    cout<<endl;
                    
                    appearances += wordIndex[s].size();
                }
            }
            if (appearances > 0)
            {
                rankedBooks.insert(&allBooks->at(i), appearances);
            }
        }
    }

    void setTopAmountBooks(int amount)
    {
        vector<Book*>* a = rankedBooks.topVector();

        vector<Book*> generalTop = *a;

        for (int i = 0; i < amount; i++)
        {
            books.addToTopBooks(generalTop.at(i));
        }
    }

    Library *getLibrary()
    {
        return &books;
    };

    void printRankedBooks()
    {
        rankedBooks.printReverseInOrder();
    };

};
#endif
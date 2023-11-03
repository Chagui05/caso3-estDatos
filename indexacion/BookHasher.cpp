#ifndef _BOOKHASHER_
#define _BOOKHASHER_ 1
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
#include <filesystem>
#include "Library.h"
using namespace std;
namespace fs = std::filesystem;

class BookHasher
{
private:
    Library books;

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

    void ranker(string search)
    {
        vector<Book> *allBooks = books.getBooks();

        for (int i = 0; i < allBooks->size(); i++)
        {
            unordered_map<string, vector<int>> wordIndex = allBooks->at(i).getWordIndex();

            if (wordIndex.find(search) != wordIndex.end())
            {

                cout << "Se encontró" << endl;
            }
            else
            {
                cout << " No se encontró" << endl;
            }
        }
    }

    vector<Book> *getAllBooks()
    {
        return books.getBooks();
    };
};
#endif
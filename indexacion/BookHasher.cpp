#ifndef _BOOKHASHER_
#define _BOOKHASHER_ 1
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
#include <filesystem>
#include "Book.h"
using namespace std;
namespace fs = std::filesystem;

class BookHasher
{
private:
    vector<Book> books;

public:
    
    BookHasher() {};

    void hashBooksInFolder(const string &folderPath)
    {
        for (const auto &file : fs::directory_iterator(folderPath))
        {
            string path = file.path();
            Book book = Book("", "", "");
            book.buildBook(path);
            cout << path << endl;
            books.push_back(book);
        }
    };

    vector<Book>* getBooks()
    {
        return &books;
    };

};
#endif
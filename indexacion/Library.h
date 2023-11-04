#ifndef _LIBRARY_
#define _LIBRARY_ 1

#include <string>
#include <vector>
#include "Book.h"

using namespace std;

class Library
{
private:
    vector<Book> allBooks;
    vector<Book*> topBooks;

public:

    Library() {};

    void addToBooks(Book &book)
    {
        allBooks.push_back(book);
    }

    void addToTopBooks(Book *book)
    {
        topBooks.push_back(book);
    }

    vector<Book>* getBooks()
    {
        return &allBooks;
    }

    vector<Book*>* getTopBooks()
    {
        return &topBooks;
    }

    void printTopBooks()
    {
        for (int i = 0; i < topBooks.size(); i++)
        {
            cout << topBooks.at(i)->getTitle() << endl;
        }
    }

};
#endif
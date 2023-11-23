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
    vector<Book>* topBooks;

public:

    void resetLibrary()
    {
        for(int i = 0; i < allBooks.size(); i++)
        {
            allBooks.at(i).resetBook();
        }
        topBooks->clear();
    }
    Library() {
        topBooks = new vector<Book>();
    };

    void addToBooks(Book &book)
    {
        allBooks.push_back(book);
    }

    void addToTopBooks(Book book)
    {
        topBooks->push_back(book);
    }

    vector<Book>* getBooks()
    {
        return &allBooks;
    }

    vector<Book>* getTopBooks()
    {
        return &allBooks;
    }
    
    void printTopBooks()
    {
        for (int i = 0; i < topBooks->size(); i++)
        {
            cout << topBooks->at(i).getTitle() << endl;
            for (int j = 0; j <topBooks->at(i).getWordMatches().size(); j++)
            {
                cout << topBooks->at(i).getWordMatches().at(j) << endl;
            }
            cout <<endl;
        }
    }

};
#endif
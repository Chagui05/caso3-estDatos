#ifndef _LIBRARY_
#define _LIBRARY_ 1

// Para almacenar todos los libros en una colección
#include <vector>
#include "book.h"
using namespace std;
class Library {
    private:
    std::vector<Book> books;

    public:

    void addToBooks(Book book){
        books.push_back(book);
    }

    vector<Book> getBooks()
    {
        return books;
    }

};

#endif
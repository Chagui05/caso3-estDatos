#ifndef _LIBCREATOR_
#define _LIBCREATOR_ 1
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
#include <cctype>
#include <filesystem>
#include "../indexacion-ranking/Library.h"
#include "../indexacion-ranking/BookOperations.h"
#include "../generic/MultiAVLImplementation.h"
using namespace std;
namespace fs = std::filesystem;


class libraryCreator : public BookOperations<Book>
{
public:
    libraryCreator(){};

    void createBooks(const string &folderPath)
    {
        for (const auto &file : fs::directory_iterator(folderPath))
        {
            string path = file.path();
            Book book = Book();
            cout << path << endl;
            book.buildBook(path); //this assigns BookVariables, and creates a hashMap and Btree for each book
            cout<<"yes"<<endl<<endl;
            books.addToBooks(book); //this adds it to the library
        }
    };


};

#endif

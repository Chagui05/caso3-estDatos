#ifndef _BOOKPROCESSER_
#define _BOOKPROCESSER_ 1

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>

#include "bookLoader.h"
#include "book.h"
#include "Library.h"

bool isRegularFile(const std::string &filePath)
{
    struct stat fileInfo;
    if (stat(filePath.c_str(), &fileInfo) != 0)
    {
        return false;
    }
    return S_ISREG(fileInfo.st_mode);
}

void processFilesInFolder(const std::string& folderPath) {
    bookLoader loader;  // Instantiate your info loader class
    Library library;

    DIR *dir;
    struct dirent *entry;

    dir = opendir(folderPath.c_str());
    cout << entry << endl;
    if (dir) {
        while ((entry = readdir(dir)) != nullptr) {
            const std::string fileName = entry->d_name;
            const std::string filePath = folderPath + "/" + fileName;
            cout << filePath << endl;

            if (isRegularFile(filePath)) {
                loader.loadBooks(library ,filePath);
                // Process the file using your loader class
            }
        }
        closedir(dir);
    }
}

int main()
{
    cout << "a" << endl;
    bookLoader prueba;
    Library books;

    prueba.loadBooks(books, "../bookDatabase/hola.txt");

    vector<Book> pru = books.getBooks();

    processFilesInFolder("../bookDatabase");

    return 0;
}

#endif
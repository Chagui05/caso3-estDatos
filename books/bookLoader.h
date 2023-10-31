#ifndef _BOOKLOADER_
#define _BOOKLOADER_ 1

#include <iostream>
#include <fstream>
#include "book.h"
#include "Library.h"

using namespace std;
class bookLoader
{
public:
    void loadBooks(Library library, const string &filePath)
    {
        ifstream file(filePath);

        if (!file)
        {
            cout << "Error al abrir el archivo: " << filePath << std::endl;
            return;
        }

        Book book;

        std::string line;
        while (std::getline(file, line))
        {
            if (line.find("Title:") == 0)
            {
                book.title = line.substr(7);
            }
            else if (line.find("Author:") == 0)
            {
                book.author = line.substr(8);
            }
            else if (line.find("Year:") == 0)
            {
                book.date = std::stoi(line.substr(6));
            }
            else
            {
                book.content += line + "\n";
            }
        }
        library.addToBooks(book);
        file.close();
        cout << book.title << endl;
        cout << book.author << endl;
        cout << book.date << endl;
    }
};

#endif
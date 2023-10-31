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
        std::getline(file,line);
        book.title = line.substr(10);
        std::getline(file,line);
        std::getline(file,line);
        book.description = line.substr(13);
        std::getline(file,line);
        std::getline(file,line);
        book.author = line.substr(8);
        std::getline(file,line);
        std::getline(file,line);
        book.date = line.substr(14);
        std::getline(file,line);
        std::getline(file,line);
        book.content = line + "\n";
        // while (std::getline(file, line))
        // {
        //     if (line.find("Title:") == 0)
        //     {
        //         book.title = line.substr(7);
        //     }
        //     else if (line.find("Author:") == 0)
        //     {
        //         book.author = line.substr(8);
        //     }
        //     else if (line.find("Year:") == 0)
        //     {
        //         book.date = std::stoi(line.substr(6));
        //     }
        //     else
        //     {
        //         book.content += line + "\n";
        //     }
        // }
        library.addToBooks(book);
        file.close();
        cout << "Title: "<<book.title << endl;
        cout << "Description: "<<book.description <<endl;
        cout << "Author: "<<book.author << endl;
        cout << "Release Date: "<<book.date << endl;
        cout << endl;
    }
};

#endif
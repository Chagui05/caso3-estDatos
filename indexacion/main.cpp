#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
#include "book.h"
using namespace std;

int main()
{
    Book book = Book("","","");
    string path = "../bookDatabase/A Christmas Carol in Prose; Being a Ghost Story of Christmas by Charles Dickens.txt";
    book.loadBook(path);

    cout << book.getTitle() << endl;
    cout << book.getDescription() << endl;
    cout << book.getAuthor() << endl;
    
}
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
#include "BookHasher.cpp"
using namespace std;

int main()
{
    Book book = Book("","","");
    string path = "txt.txt";

    book.buildBook(path);
    book.printWordIndex();

    BookHasher bookHasher = BookHasher();
    bookHasher.hashBooksInFolder("../bookDatabase");
    
};
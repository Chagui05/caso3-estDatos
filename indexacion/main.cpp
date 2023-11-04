#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
#include "BookHasher.h"
using namespace std;

int main()
{
    // Book book = Book("","","");
    // string path = "txt.txt";

    // book.buildBook(path);
    // book.printWordIndex();

    BookHasher bookHasher = BookHasher();
    bookHasher.hashBooksInFolder("../bookDatabase");

    // bookHasher.getAllBooks()->at(0).printWordIndex();
    
    vector<string> search;

    search.push_back("Musketeers");
    search.push_back("Alexandre");
    search.push_back("fourth");
    search.push_back("hello");
    search.push_back("magic");
    search.push_back("attempt");

    cout <<endl<<endl;
    cout << "RANK THE BOOKS BY THIS WORD: "; for(string s: search){ cout << s << " "; }
    cout <<endl<<endl;

    bookHasher.getMultiSetAVL(search);

    cout <<endl<<endl;
    cout << "BOOKS RANKED" << endl;
    int num = 10;
    cout << "Top: " << num << endl;

    bookHasher.setTopAmountBooks(num);

    bookHasher.getLibrary()->printTopBooks();
    
};
#ifndef _BOOKHASHER_
#define _BOOKHASHER_ 1
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
#include <cctype>
// #include <filesystem>
#include "../indexacion-ranking/Library.h"
#include "../indexacion-ranking/BookOperations.h"
#include "../generic/MultiAVLImplementation.h"
using namespace std;
// namespace fs = std::filesystem;

class BookHasher : public BookOperations<Book>
{
private:
    MultisetAVLTree<Book> ranked;
public:
    BookHasher(){};
    BookHasher(Library *libs)
    {
        books = *libs;
    };
    // void hashBooksInFolder(const string &folderPath)
    // {
    //     for (const auto &file : fs::directory_iterator(folderPath))
    //     {
    //         string path = file.path();
    //         Book book = Book();
    //         cout << path << endl;
    //         book.buildBook(path);
    //         cout<<"yes"<<endl<<endl;
    //         books.addToBooks(book);
    //     }
    // };

    void getRankedMultiSetAVL(vector<string> search)
    {
        vector<Book>* allBooks = books.getBooks();
        ranked = MultisetAVLTree<Book>();

        for (int i = 0; i < allBooks->size(); i++)
        {
            unordered_map<string, vector<int>> wordIndex = allBooks->at(i).getWordIndex();
            int appearances = 0;
            for (string s : search)
            {
                toLowerCase(s);
                if (wordIndex.find(s) != wordIndex.end())
                {
                    string title = allBooks->at(i).getTitle();
                    allBooks->at(i).addWordMatch(s);
                    appearances += wordIndex[s].size();
                }
            }
            if (appearances > 0)
            {
                ranked.insert(&allBooks->at(i), appearances);
            }
        }
    }

    void setTopAmountBooks(int amount)
    {
        vector<Book*>* top10 = ranked.topVector();

        for (int i = 0; i < amount; i++)
        {
            cout <<"adding: "<< top10->at(i)->getTitle();
            Book adding = *top10->at(i);
            books.addToTopBooks(adding);
        }
    }

    vector<Book>* getTop10Books()
    {
        vector<Book*>* top = ranked.topVector();
        vector<Book>* top10Books = new vector<Book>();
        int tenOrLess = 10;
        
        if(top->size() < 10)
        {
            cout<< "size"<< top->size()<<endl;
            tenOrLess = top->size();
        }
        
        for (int i = 0; i < tenOrLess; i++)
        {
            cout <<"adding: "<< top->at(i)->getTitle();
            top10Books->push_back(*top->at(i));
        }

        return top10Books;
    }

    void printRankedBooks()
    {
        ranked.printReverseInOrder();
    };

};

#endif
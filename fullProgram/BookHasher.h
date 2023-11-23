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

        for (int i = 0; i < allBooks->size(); i++)//itera por cada libro
        {
            unordered_map<string, vector<int>> wordIndex = allBooks->at(i).getWordIndex();//obtiene hasmap de palabras de cada libro
            int appearances = 0;
            for (string word : search)//itera en palabras a buscar
            {
                toLowerCase(word);
                if (wordIndex.find(word) != wordIndex.end())//revisa si las palabras estan en el hasmap del libro
                {
                    string title = allBooks->at(i).getTitle();
                    allBooks->at(i).addWordMatch(word);//agrega la palabra a wordmatches, se usa luego
                    appearances += wordIndex[word].size(); // el size de ese vector es la cantidad de apariciones, por lo tanto la cant de apariciones,lo suma a las del libro
                }
            }
            if (appearances > 0)//despues de recorrer cada palabra ve el puntaja total del libro, si es mayor a 0 lo agrega al multiset
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
        vector<Book*>* top = ranked.topVector();//saca el vector de todos los libros rankeados de mejor a peor
        vector<Book>* top10Books = new vector<Book>();
        int tenOrLess = 10;
        
        if(top->size() < 10)
        {
            cout<< "size"<< top->size()<<endl;
            tenOrLess = top->size();// esto asigna a menos en caso de que no se encontran 10 libros o mas 
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
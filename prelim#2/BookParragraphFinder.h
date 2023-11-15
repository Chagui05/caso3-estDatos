#ifndef _BOOKPARR_
#define _BOOKPARR_ 1
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
#include <cctype>
#include "../indexacion-ranking/Library.h"
#include "../indexacion-ranking/BookOperations.h"
#include "../generic/MultiAVLImplementation.h"
#include "ParagraphRating.h"

using namespace std;

class BookParragraphFinder : public BookOperations<Parragraph>
{
private:
    vector<Book> *top10Books;
    vector<Parragraph *> *top30Parragraphs;

public:
    BookParragraphFinder()
    {
        top30Parragraphs = new vector<Parragraph *>();
    };

    BookParragraphFinder(vector<Book> *top10)
    {
        top10Books = top10;
        top30Parragraphs = new vector<Parragraph *>();
    }

    void findAppearences()
    {
        for (int i = 0; i < top10Books->size(); i++)
        {
            Book book = top10Books->at(i);
            cout << book.getTitle() << endl;
            for (int j = 0; j < book.getWordMatches().size(); j++)
            {
                string lookFor = book.getWordMatches().at(j);
                cout << "buscando " << lookFor << endl;

                Word *word = book.getBtree()->search(lookFor)->getKey(lookFor);
                cout << "se encontro la palabra: " << *word->key << " " << lookFor << endl;
                if (word != nullptr)
                {
                    for (int k = 0; k < word->description->size(); k++)
                    {
                        // cout<<*word->key << " :word"<< "description: " <<*word->description->at(k) << endl;//TODO: esta imprimiendo el mismos para todos
                        
                        
                        int *rating = new int(calculateRating(*word->description->at(k), book.getWordMatches()));
                        cout << "rating: " << *rating << endl;
                        string *title = new string(book.getTitle());
                        string *author = new string(book.getAuthor());
                        string *filePath = new string(book.getFilePath());

                        Parragraph parra = Parragraph(title, author, word->description->at(k), filePath, word->pages->at(k), rating);
                        book.addToMultiSetAVL(parra);//TODO: check the pointers
                        delete rating;
                        delete title;
                        delete author;
                        delete filePath;
                    }
                }
            }
            cout << endl;
        }
    }

    void setTop30Parragraphs()
    {
        cout << "TOP 30 PARRAGRAPHS" << endl;


        for (int i = 0; i < top10Books->size(); i++)
        {
            vector<Parragraph*>* parragraphs = top10Books->at(i).getAllParragraphsRanked()->topVector(); 
            for (int j = 0; j < 3; j++)
            {
                top30Parragraphs->push_back(parragraphs->at(j)); // TODO: check the pointers
            }
            delete parragraphs;
        }
    }

    vector<Parragraph*>* getTop30Parragraphs()
    {
        return top30Parragraphs;
    }   

};
#endif
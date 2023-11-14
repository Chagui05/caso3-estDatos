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
    BookParragraphFinder(){};

    BookParragraphFinder(vector<Book> *top10)
    {
        top10Books = top10;
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
                cout << "se encontro la palabra: " << *word->key << " " << lookFor << endl
                     << endl;
                if (word != nullptr)
                {
                    for (int k = 0; k < word->description->size(); k++)
                    {
                        cout << (word->description->at(k) == nullptr) << endl;
                        cout << "page: " << *(word->pages->at(k)) << endl;
                        int *rating = new int(calculateRating(*word->description->at(k), book.getWordMatches()));
                        string *title = new string(book.getTitle());
                        string *author = new string(book.getAuthor());
                        string *filePath = new string(book.getFilePath());

                        Parragraph parra = Parragraph(title, author, word->description->at(k), filePath, word->pages->at(k), rating);
                        delete rating;
                        delete title;
                        delete author;
                        delete filePath;
                        book.addToMultiSetAVL(parra);//TODO: check the pointers
                    }
                }
            }
            cout << endl;
        }
    }

    void setTop30Parragraphs()
    {
        for (int i = 0; i < top10Books->size(); i++)
        {
            vector<Parragraph *> *parragraphs = top10Books->at(i).getAllParragraphsRanked().topVector(); // TODO: check the pointers
            for (int j = 0; j < 3; j++)
            {
                top30Parragraphs->push_back(parragraphs->at(j)); // TODO: check the pointers
            }
        }
    }
};
#endif
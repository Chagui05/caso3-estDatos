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
#include "ParagraphRating.h"//TODO: check the directory

using namespace std;

class BookParragraphFinder : public BookOperations<Parragraph>
{
private:
    vector<Book> *top10Books;
    vector<Parragraph*> *top30Parragraphs;//TODO: check the pointers

public:
    BookParragraphFinder(){};

    BookParragraphFinder(vector<Book> *top10)
    {
        top10Books = top10;
    }

    // void findAppearences()
    // {
    //     for (int i = 0; i < top10Books->size(); i++)
    //     {
    //         Book book = top10Books->at(i);
    //         cout << book.getTitle() << endl;
    //         for (int j = 0; j < book.getWordMatches().size(); j++)
    //         {
    //             cout << book.getWordMatches().at(j) << endl;
    //             Word word = book.getBtree().search(book.getWordMatches().at(j));
    //             cout << "se encontro la palabra: " << word.key << endl
    //                  << endl;
    //             if (word.key != "Key not found")
    //             {
    //                 for (int k = 0; k < word.description.size(); k++)
    //                 {
    //                     int rating = calculateRating(word.description.at(k), book.getWordMatches());
    //                     Parragraph parra = Parragraph(book.getTitle(), book.getAuthor(), word.description.at(k), book.getFilePath(), word.pages.at(k), rating);
    //                     book.addToMultiSetAVL(parra);//TODO: check the pointers 
    //                 }
    //             }
    //         }
    //         cout << endl;
    //     }
    // }

    void setTop30Parragraphs()
    {
        for (int i = 0; i < top10Books->size(); i++)
        {
            vector<Parragraph*>* parragraphs = top10Books->at(i).getAllParragraphsRanked().topVector();//TODO: check the pointers
            for (int j = 0; j < 3; j++)
            {
                top30Parragraphs->push_back(parragraphs->at(j));//TODO: check the pointers
            }
        }
    }
};
#endif
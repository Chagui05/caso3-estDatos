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
#include "../prelim#2/Parragraph.h"
#include "../prelim#2/ParagraphRating.h"

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

    BookParragraphFinder(vector<Book> top10)
    {
        top30Parragraphs = new vector<Parragraph *>();
    }

    void findAppearences(vector<Book> top10)
    {
        top10Books = new vector<Book>(top10);
        for (int i = 0; i < top10Books->size(); i++)
        {
            Book book = top10Books->at(i);
            // cout << "Book: " << book.getTitle() << endl;
            for (int j = 0; j < book.getWordMatches().size(); j++)
            {
                string lookFor = book.getWordMatches().at(j);

                // cout << "buscando " << lookFor << endl;
                Word *word = book.getBtree()->search(lookFor);//TODO: 
                if (word != nullptr)
                {
                    for (int k = 0; k < word->description->size(); k++)
                    {
                        int *rating = new int(calculateRating(*word->description->at(k), book.getWordMatches()));
                        string *title = new string(book.getTitle());
                        string *author = new string(book.getAuthor());
                        string *filePath = new string(book.getFilePath());
                        Parragraph* parra = new Parragraph(title, author, word->description->at(k), filePath, word->pages->at(k), rating, word->key);
                        book.addToMultiSetAVL(parra);
                //         // delete rating;
                //         // delete title;
                //         // delete author;
                //         // delete filePath;
                    }
                }
            }
            cout << endl;
        }
    }

    void setTop30Parragraphs()
    {
        cout << "TOP 30 PARRAGRAPHS" << endl;
        top30Parragraphs = new vector<Parragraph *>();
        for (int i = 0; i < top10Books->size(); i++)
        {
            vector<Parragraph*>* parragraphs = top10Books->at(i).getAllParragraphsRanked()->topVector(); 
            
            if(parragraphs->size() < 3)
            {
                for(int k = 0; k < parragraphs->size(); k++)
                {
                    Parragraph *insertPar = new Parragraph(*parragraphs->at(k));
                    top30Parragraphs->push_back(insertPar); 
                }
            }
            else
            {
                for (int j = 0; j < 3; j++)
                {
                    Parragraph *insertPar = new Parragraph(*parragraphs->at(j));
                    top30Parragraphs->push_back(insertPar); 
                }
            }    
        }
    }

    vector<Parragraph*>* getTop30Parragraphs()
    {
        return top30Parragraphs;
    }   

};
#endif
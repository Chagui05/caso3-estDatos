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
        top10Books = new vector<Book>(top10);
        top30Parragraphs = new vector<Parragraph *>();
    }

    void findAppearences()
    {
        for (int i = 0; i < top10Books->size(); i++)//itera por cada libro
        {
            Book book = top10Books->at(i);
            for (int j = 0; j < book.getWordMatches().size(); j++)//iteramos por cada wordMatch previamente encontrado
            {
                string lookFor = book.getWordMatches().at(j);//saca la palabra a buscar

              
                Word *word = book.getBtree()->search(lookFor); 
                if (word != nullptr) //revisa que no haya sacado un nullptr
                {
                    for (int k = 0; k < word->description->size(); k++) // obtiene cada parrafo que habia en el word
                    {
                        int *rating = new int(calculateRating(*word->description->at(k), book.getWordMatches())); // se calcula el rating
                        string *title = new string(book.getTitle());//se obtienen dtos del libro
                        string *author = new string(book.getAuthor());//se obtienen dtos del libro
                        string *filePath = new string(book.getFilePath());//se obtienen dtos del libro
                        string *image = new string(book.getRandomImageURl());//se obtienen dtos del libro
                        Parragraph* parra = new Parragraph(title, author, word->description->at(k), filePath, word->pages->at(k), rating, word->key,image);
                        book.addToMultiSetAVL(parra);//se agrega al top de parrafos del libro, luego se depuraran los 3 mejores
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
        for (int i = 0; i < top10Books->size(); i++)//itera por cada libro del top 10
        {
            vector<Parragraph*>* parragraphs = top10Books->at(i).getAllParragraphsRanked()->topVector(); //obtiene los mejores parrafos del libro
                                                                                                         //con base en el AVL que se insertaron en findApperaences
            if(parragraphs->size() < 3)//sp;p agarrar los 3 mejores
            {
                for(int k = 0; k < parragraphs->size(); k++)
                {
                    Parragraph *insertPar = new Parragraph(*parragraphs->at(k));
                    top30Parragraphs->push_back(insertPar); //se insertan en el top 30 de parrafos globales 
                }
            }
            else//en caso de que haya menos de 3 solo agarra esos
            {
                for (int j = 0; j < 3; j++)
                {
                    Parragraph *insertPar = new Parragraph(*parragraphs->at(j));
                    top30Parragraphs->push_back(insertPar); //se insertan en el top 30 de parrafos globales 
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
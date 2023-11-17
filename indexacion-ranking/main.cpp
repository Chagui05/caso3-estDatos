#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
#include "BookHasher.h"
#include "../prelim#2/BookParragraphFinder.h"
using namespace std;

int main()
{

    BookHasher bookHasher = BookHasher();
    bookHasher.hashBooksInFolder("../bookDatabase");

    vector<string> search;

     search.push_back("Musketeers");
     search.push_back("Alexandre");
     search.push_back("fourth");
     search.push_back("hello");
     search.push_back("magic");
     search.push_back("attempt");
    search.push_back("gutenbergtm");
    search.push_back("gutenberg");
    search.push_back("carpenter");
    search.push_back("howling");
    search.push_back("enmanciparmente");


     cout <<endl<<endl;
     cout << "RANK THE BOOKS BY THIS WORD: "; for(string s: search){ cout << s << " "; }
     cout <<endl<<endl;

     bookHasher.getRankedMultiSetAVL(search);

    
    cout << "BOOKS RANKED" << endl;
    int num = 3;
   cout << "Top 10: " << endl;

    bookHasher.setTopAmountBooks(num);

    vector<Book>* top10 = bookHasher.getTop10Books();

    for(int i = 0; i < top10->size(); i++)
     {
       cout<<i+1<<". ";
       cout << top10->at(i).getTitle() << endl;
      
     }
    cout<<endl<<endl;
    cout <<"busqueda de parrafos"<<endl<<endl;
   BookParragraphFinder finder = BookParragraphFinder(top10);
   finder.findAppearences();
   finder.setTop30Parragraphs();
  vector<Parragraph*>* top30 = finder.getTop30Parragraphs();

  for(int j = 0; j < top30->size(); j++)
  {
    cout <<j+1<<". "<<*top30->at(j)->getBookTitle()<<endl;
  }

    




    //cout<<"inicio"<<endl; 
    //Book* book = new Book();
    //string path = "../bookDatabase/A Christmas Carol in Prose; Being a Ghost Story of Christmas by Charles Dickens.txt";
    //book->loadBtree(path);
    //book->getBtree()->traverse();
    //bool see = book->getBtree()->isEmpty();
    //cout << (see==false) << endl;

  // Word* result = book->getBtree()->search("gutenbergtm");

  // if (*result->key != "Key not found")
  // {
  //   cout << "Key found: " << result->key << endl;
  //   cout << "Description: ";
  //   // for (string*desc : result->description)
  //   // {
  //   //   cout << desc << " ";
  //   // }
  //   // cout << endl;
  //   // cout << "Pages: ";
  //   // for (const auto &page : result->pages)
  //   // {
  //   //   cout << page << " ";
  //   // }
  //   cout << endl;
  // }
  // else
  // {
  //   cout << *result->key << endl;
  // }

  return 0;
};
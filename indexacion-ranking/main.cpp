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

    // BookHasher bookHasher = BookHasher();
    // bookHasher.hashBooksInFolder("../bookDatabase");

    // vector<string> search;

    // search.push_back("Musketeers");
    // search.push_back("Alexandre");
    // search.push_back("fourth");
    // search.push_back("hello");
    // search.push_back("magic");
    // search.push_back("attempt");

    // cout <<endl<<endl;
    // cout << "RANK THE BOOKS BY THIS WORD: "; for(string s: search){ cout << s << " "; }
    // cout <<endl<<endl;

    // bookHasher.getRankedMultiSetAVL(search);

    // // cout <<endl<<endl;
    // // cout << "BOOKS RANKED" << endl;
    // // int num = 3;
    // cout << "Top 10: " << endl;

    // // bookHasher.setTopAmountBooks(num);

    // vector<Book>* top10 = bookHasher.getTop10Books();

    // for(int i = 0; i < top10->size(); i++)
    // {
    //   cout<<i+1<<". ";
    //   cout << top10->at(i).getTitle() << endl;
      
    // }

    // cout <<"busqueda de parrafos"<<endl<<endl;
    // BookParragraphFinder finder = BookParragraphFinder(top10);
    // finder.findAppearences();

    




    cout<<"inicio"<<endl; 
    Book book = Book();
    string path = "../bookDatabase/Adventures of Huckleberry Finn by Mark Twain.txt";
    book.loadBtree(path);
    // book.getBtree().traverse();



  //   Word result = book.getBtree().search("magic");

  // if (result.key != "Key not found")
  // {
  //   cout << "Key found: " << result.key << endl;
  //   cout << "Description: ";
  //   for (const auto &desc : result.description)
  //   {
  //     cout << desc << " ";
  //   }
  //   cout << endl;
  //   cout << "Pages: ";
  //   for (const auto &page : result.pages)
  //   {
  //     cout << page << " ";
  //   }
  //   cout << endl;
  // }
  // else
  // {
  //   cout << "Key not found" << endl;
  // }

  return 0;
};
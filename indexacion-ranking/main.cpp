#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
// #include <thread>
#include <chrono>
#include <vector>
#include "BookHasher.h"
#include "../prelim#2/BookParragraphFinder.h"
using namespace std;
//g++ -std=c++17 -pthread main.cpp -o prueba.o
int main()
{
  cout <<"Loading Books..."<<endl;
  BookHasher bookHasher = BookHasher();
  bookHasher.hashBooksInFolder("../bookDatabase");
  vector<string> search;

  search.push_back("Musketeers");
  search.push_back("Alexandre");
  search.push_back("fourth");
  search.push_back("hello");
  search.push_back("magic");
  search.push_back("attempt");
  search.push_back("carpenter");
  //search.push_back("howling");
  //search.push_back("enmanciparmente");


  // std::this_thread::sleep_for(chrono::seconds(3));

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
  
  // std::this_thread::sleep_for(chrono::seconds(3));

  cout <<"Looking for the parragraphs..."<<endl<<endl;
  BookParragraphFinder finder = BookParragraphFinder(top10);
  finder.findAppearences();
  finder.setTop30Parragraphs();
  vector<Parragraph*>* top30 = finder.getTop30Parragraphs();
  for(int j = 0; j < top30->size(); j++)
  {
    cout <<j+1<<". "<<*top30->at(j)->getBookTitle()<<endl;
  }

  return 0;
};
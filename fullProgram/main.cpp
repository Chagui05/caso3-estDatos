#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
#include "BookHasher.h"
#include "BookParragraphFinder.h"
#include "libraryCreator.h"
#include "../phraseDecomposer/PhraseDecomposer.h"
using namespace std;
//g++ -std=c++17 -pthread main.cpp -o prueba.o
int main()
{
  cout <<"Loading Books..."<<endl;
  libraryCreator creator = libraryCreator();
  creator.createBooks("../bookDataBase");

  Library* libs = creator.getLibrary();
  cout <<"Books Loaded!!!!"<<endl<<endl;

  PhraseDecomposer decomposer = PhraseDecomposer();
  vector<string> search = decomposer.getWords("This is the prompt we are searching, in order to find the books that contain this words, no im going to paste a part from a book: I arrived at Geneva. My father and Ernest yet lived, but the former sunk under the tidings that I bore");
  
  cout <<endl<<endl;
  BookHasher bookHasher = BookHasher(libs);
  cout << "RANK THE BOOKS BY THIS WORD: "; for(string s: search){ cout << s << " "; }
  cout <<endl<<endl;

  bookHasher.getRankedMultiSetAVL(search);

    
  cout << "BOOKS RANKED" << endl;
  cout << "Top 10: " << endl;
  vector<Book>* top10 = bookHasher.getTop10Books();
  for(int i = 0; i < top10->size(); i++)
  {
    cout<<i+1<<". "<< top10->at(i).getTitle() << endl;
  }
  
  cout<<endl<<endl;

  cout <<"Looking for the parragraphs..."<<endl<<endl;
  vector<Book> newTop10 = *top10;
  
  BookParragraphFinder finder = BookParragraphFinder();
  finder.findAppearences(newTop10);
  finder.setTop30Parragraphs();
  vector<Parragraph*>* top30 = finder.getTop30Parragraphs();
  for(int j = 0; j < top30->size(); j++)
  {
    cout <<j+1<<". "<<top30->at(j)->getRating()<< " " << *top30->at(j)->getBookTitle() << endl;
  }

  return 0;
};
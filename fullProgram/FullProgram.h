#ifndef _FULLPROGRAM_
#define _FULLPROGRAM_ 1
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
#include <cctype>
#include <filesystem>
#include "../indexacion-ranking/Library.h"
#include "../indexacion-ranking/BookOperations.h"
#include "../generic/MultiAVLImplementation.h"
#include "BookHasher.h"
#include "BookParragraphFinder.h"
#include "../phraseDecomposer/PhraseDecomposer.h"
#include "../aiAPI/AIQuestions.h"
#include "../SynonymsApi/SynonymsApi.h"


using namespace std;
namespace fs = std::filesystem;


class FullProgram : public BookOperations<Book>
{
private:
    AIQuestions asker = AIQuestions("APIKEYHERE"); //this is the API key
public:
    FullProgram(){};

    void createBooks(const string &folderPath)
    {
        for (const auto &file : fs::directory_iterator(folderPath))
        {
            string path = file.path();
            Book book = Book();
            cout << path << endl;
            book.buildBook(path); //this assigns BookVariables, and creates a hashMap and Btree for each book
            cout<<"yes"<<endl<<endl;
            books.addToBooks(book); //this adds it to the library
        }
    };

    string run(string phrase)
    {
        PhraseDecomposer decomposer = PhraseDecomposer();
        vector<string> search = decomposer.getWordAndSynonyms(decomposer.getWords(phrase));
        
        cout <<endl<<endl;

        Library* libs = new Library(books);
        libs->resetLibrary();

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
        
        BookParragraphFinder finder = BookParragraphFinder(newTop10);
        finder.findAppearences();
        finder.setTop30Parragraphs();
        vector<Parragraph*>* top30 = finder.getTop30Parragraphs();

        //question for ChatGPT

        for(int j = 0; j < top30->size(); j++)
        {
            string question = "give me a feeling (just a word) based on this: ";
            // cout <<j+1<<". "<<top30->at(j)->getRating()<< " " << *top30->at(j)->getContent()<< endl;
            cout <<j+1<<". "<<*top30->at(j)->getBookTitle()<<" "<<*top30->at(j)->getWordContained()<<endl;
            //set the feeling and image
            question += *top30->at(j)->getContent();
            // string *feeling = asker.askQuestion(question);TODO: uncomment this
            // string *image = asker.genImage(*feeling);
            // top30->at(j)->setFeeling(feeling);
            // top30->at(j)->setImage(image);

            top30->at(j)->setFeeling(new string("feeling"));
            top30->at(j)->setImage(new string("https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcQuxqrYaFZR02ygglW1h3uQYTfkCqsvN5G6lblfKhDFJwcFCZgT7M0X58y-SrFIeCqqWT8&usqp=CAU"));
            question = "";
        }

        string serialized = serializeParragraps(*top30);
        return serialized;
    };


    string serializeParragraps(vector<Parragraph*> paragraphs) 
    {
    json jsonArray;
    for (int i = 0; i < paragraphs.size(); i++) {
        json paragraphJson;
        paragraphJson["bookTitle"] = *paragraphs.at(i)->getBookTitle();
        paragraphJson["wordContained"] = *paragraphs.at(i)->getWordContained();
        paragraphJson["bookAuthor"] = *paragraphs.at(i)->getBookAuthor();
        paragraphJson["content"] = *paragraphs.at(i)->getContent();
        paragraphJson["filePath"] = *paragraphs.at(i)->getFilePath();
        paragraphJson["feeling"] = *paragraphs.at(i)->getFeeling();
        paragraphJson["image"] = *paragraphs.at(i)->getImage();
        paragraphJson["page"] = *paragraphs.at(i)->getPage();
        paragraphJson["rating"] = paragraphs.at(i)->getRating();
        jsonArray.push_back(paragraphJson);
    }
    return jsonArray.dump();
}



};

#endif
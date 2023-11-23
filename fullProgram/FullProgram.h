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
#include "../SentimentApi/SentimentApi.h"
#include "../SynonymsApi/SynonymsApi.h"
// #include "../aiAPI/AIQuestions.h"


using namespace std;
namespace fs = std::filesystem;


class FullProgram : public BookOperations<Book>
{
private:
    ApiGetter api;
    //AIQuestions apiQuestioner = AIQuestions("APIKEYHERE")
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
        vector<string> search = decomposer.getWords(phrase);
        // vector<string> search = decomposer.getWordAndSynonyms(decomposer.getWords(phrase));
        
        cout <<endl<<endl;

        Library* libs = new Library(books);//ese books es el propio de la clase, lo convertimos a puntero
        libs->resetLibrary();//reseteamos para que no se acumulen: wordmatches, top3parragraphs, etc

        BookHasher bookHasher = BookHasher(libs);
        cout << "RANK THE BOOKS BY THIS WORD: "; for(string s: search){ cout << s << " "; }
        cout <<endl<<endl;

        bookHasher.getRankedMultiSetAVL(search);

            
        cout << "BOOKS RANKED" << endl;
        cout << "Top 10: " << endl;
        vector<Book>* top10 = bookHasher.getTop10Books();//sacamos los 10 mejores libros del AVL de BookHaser
        for(int i = 0; i < top10->size(); i++)
        {
            cout<<i+1<<". "<< top10->at(i).getTitle() << endl;//imprime los mejores
        }
        
        cout<<endl<<endl;

        cout <<"Looking for the parragraphs..."<<endl<<endl;
        vector<Book> newTop10 = *top10;//dereferencia el top10 a un vector de libros
        
        BookParragraphFinder finder = BookParragraphFinder(newTop10); //crea un BookParragraphFinder con el vector de libros
        finder.findAppearences();// busca las apariciones de las palabras en los 10 libros
        finder.setTop30Parragraphs(); //fija los mejores 3 parrafos por cada libro
        vector<Parragraph*>* top30 = finder.getTop30Parragraphs(); //saca los 30 mejores parrafos


        for(int j = 0; j < top30->size(); j++)//proceso de asignar sentimiento para cada parrafo
        {
            cout <<j+1<<". "<<*top30->at(j)->getBookTitle()<<" "<<*top30->at(j)->getWordContained()<<endl;//esto enseña los parrafos y sus atributos

            //set the feeling and image
            string wordToAnalyze = *top30->at(j)->getWordContained();//saca la palabra del match 
            string* sentiment = new string(api.getSentimentString(wordToAnalyze));// con base en esa palabra saca el sentimiento con sentimentApi
            top30->at(j)->setFeeling(sentiment);//setea el sentimiento
            cout<<"Feeling: "<<*sentiment<<endl<<endl;

            // top30->at(j)->setFeeling(new string("feeling"));
            // top30->at(j)->setImage(new string("https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcQuxqrYaFZR02ygglW1h3uQYTfkCqsvN5G6lblfKhDFJwcFCZgT7M0X58y-SrFIeCqqWT8&usqp=CAU"));
        
            //OPEN AI ALTERNATIVE
            // string* feeling = apiQuestioner.parragraphQuestion(*top30->at(j)->getContent());
            // top30->at(j)->setFeeling(feeling);
            // string* image = apiQuestioner.genImage(*feeling);
            // top30->at(j)->setImage(image);
        }

        string serialized = serializeParragraps(*top30);//se serializan los parrafos para luego ser enviados al servidor web
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
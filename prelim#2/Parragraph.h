#ifndef _PARRAGRAPH_
#define _PARRAGRAPH_ 1
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
using namespace std;

class Parragraph
{
private:
    string bookTitle;
    string bookAuthor;
    string content;
    string filePath;
    vector<string> wordMatches;
    int page;
    int rating;

public:
    Parragraph() {}
    Parragraph(string bookTitle, string bookAuthor, string content, string filePath, int page, int rating)
    {
        this->bookTitle = bookTitle;
        this->bookAuthor = bookAuthor;
        this->content = content;
        this->filePath = filePath;
        this->page = page;
        this->rating = rating;
    }
    vector<string> getWordMatches()
    {
        return wordMatches;
    }

    int getRating()
    {
        return rating;
    }

    int getPage()
    {
        return page;
    }

    /*
    string feeling
    Image image 
    */

};
#endif

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
    string* bookTitle;
    string* wordContained;
    string *bookAuthor;
    string *content;
    string *filePath;
    string* feeling;
    string* image;
    int* page;
    int *rating;

public:
    Parragraph() {}
    Parragraph(string* bookTitle, string* bookAuthor, string* content, string* filePath, int* page, int* rating, string* wordContained)
    {
        this->bookTitle = bookTitle;
        this->bookAuthor = bookAuthor;
        this->content = content;
        this->filePath = filePath;
        this->page = page;
        this->rating = rating;
        this->wordContained = wordContained;
        this->feeling = new string();
        this->image = new string();
    }

    int getRating()
    {
        return *rating;
    }

    int* getPage()
    {
        return page;
    }

    string* getContent()
    {
        return content;
    }

    string* getBookTitle()
    {
        return bookTitle;
    }

    string* getWordContained()
    {
        return wordContained;
    }

    string* getBookAuthor()
    {
        return bookAuthor;
    }

    string* getFilePath()
    {
        return filePath;
    }
    
    string* getFeeling()
    {
        return feeling;
    }
    string* getImage()
    {
        return image;
    }

    void setFeeling(string* feeling)
    {
        this->feeling = feeling;
    }
    void setImage(string* image)
    {
        this->image = image;
    }

};
#endif

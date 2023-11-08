#ifndef _BOOKPARR_
#define _BOOKPARR_ 1
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

using namespace std;
namespace fs = std::filesystem;

class BookParragraphFinder : public BookOperations<Parragraph>
{
public:

    BookParragraphFinder(){};

    BookParragraphFinder(Library &library)
    {
        books = library;
    };
};
#endif
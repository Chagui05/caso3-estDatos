#ifndef _BOOKOPER_
#define _BOOKOPER_ 1
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
#include <cctype>
#include "Library.h"
#include "../generic/MultiAVLImplementation.h"
using namespace std;

template<typename T>
class BookOperations
{
protected:
    Library books;
    MultisetAVLTree<T> ranked;

public:

    Library *getLibrary()
    {
        return &books;
    };

    T *getRankedElements()
    {
        return &ranked;
    };

    
};
#endif
#ifndef _LIBRARY_
#define _LIBRARY_ 1

// Para almacenar todos los libros en una colección
#include <vector>
#include "book.h"
using namespace std;
class Library {
    public:
    std::vector<book> library;

};

#endif
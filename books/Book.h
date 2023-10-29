#ifndef _BOOK_
#define _BOOK_ 1

#include <string>
#include <vector>
struct book {
    std::string title;
    std::string description;
    std::string author;
    std::string date;
    std::string content;  // El contenido del libro como una cadena de texto
    
};
std::vector<book> library;



#endif
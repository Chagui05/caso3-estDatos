#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstring>
#include "../books/Book.h"
#include "../books/Library.h"

// Estructura para representar un libro y su relevancia (TF-IDF)
struct BookRelevance {
    int bookIndex;
    double relevance;
};

// Función para calcular el TF-IDF de una palabra clave en un libro
double calculateTFIDF(const std::string& keyword, const book& book, const std::vector<book>& library) {
    int termFrequency = 0;
    for (char* p = &book.content[0]; (p = strstr(p, keyword.c_str())); p++) {
        termFrequency++;
    }

    int documentFrequency = 0;
    for (const book& otherBook : library) {
        if (otherBook.content.find(keyword) != std::string::npos) {
            documentFrequency++;
        }
    }

    if (documentFrequency == 0) {
        return 0.0;
    }

    double tf = static_cast<double>(termFrequency) / book.content.length();
    double idf = log(static_cast<double>(library.size()) / documentFrequency);

    return tf * idf;
}

// Función para calcular el ranking de libros basado en palabras clave ingresadas por el usuario
std::vector<BookRelevance> calculateRanking(const std::vector<std::string>& userKeywords, const std::vector<book>& library) {
    std::vector<BookRelevance> ranking;

    for (int i = 0; i < library.size(); i++) {
        double relevance = 0.0;
        for (const std::string& keyword : userKeywords) {
            relevance += calculateTFIDF(keyword, library[i], library);
        }

        if (relevance > 0.0) {
            BookRelevance bookRelevance;
            bookRelevance.bookIndex = i;
            bookRelevance.relevance = relevance;
            ranking.push_back(bookRelevance);
        }
    }

    // Ordenar la lista de libros por relevancia (mayor a menor)
    std::sort(ranking.begin(), ranking.end(), [](const BookRelevance& a, const BookRelevance& b) {
        return a.relevance > b.relevance;
    });

    return ranking;
}

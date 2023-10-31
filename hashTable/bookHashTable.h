#ifndef _BOOKHASHTABLE_
#define _BOOKHASHTABLE_ 1

#include <iostream>
#include <string>
#include <vector>
#include <list>

const int TABLE_SIZE = 100; // Tamaño de la tabla hash

// Estructura para un elemento en la tabla hash
struct HashNode {
    std::string keyword;
    std::vector<int> books; // Índices de los libros en la biblioteca
};

// Tabla hash como una matriz de listas enlazadas
std::list<HashNode> hashTable[TABLE_SIZE];

// Función de hash simple (puede ser mejorada)
int hashFunction(const std::string& key) {
    int hash = 0;
    for (char c : key) {
        hash += static_cast<int>(c);
    }
    return hash % TABLE_SIZE;
}

// Función para insertar una palabra clave y su libro asociado en la tabla hash
void insertIntoHashTable(const std::string& key, int bookIndex) {
    int hashValue = hashFunction(key);

    // Buscar si la palabra clave ya existe en la lista enlazada
    for (auto& node : hashTable[hashValue]) {
        if (node.keyword == key) {
            // La palabra clave ya existe, agrega el índice del libro a la lista de libros
            node.books.push_back(bookIndex);
            return;
        }
    }

    // Si la palabra clave no existe, crea un nuevo nodo y agrégalo a la lista enlazada
    HashNode newNode;
    newNode.keyword = key;
    newNode.books.push_back(bookIndex);
    hashTable[hashValue].push_back(newNode);
}

#endif;
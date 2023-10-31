#ifndef _BOOKAVL_
#define _BOOKAVL_ 1

#include <string>
#include <vector>
#include <iostream>

// Estructura para un nodo del Árbol AVL
struct AVLNode {
    std::string keyword;
    std::vector<int> books;  // Índices de los libros en la biblioteca

    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(const std::string& key, int bookIndex) : keyword(key), left(nullptr), right(nullptr), height(1) {
        books.push_back(bookIndex);
    }
};

// Función para obtener la altura de un nodo
int getHeight(AVLNode* node) {
    return (node != nullptr) ? node->height : 0;
}

// Función para obtener el factor de equilibrio de un nodo
int getBalanceFactor(AVLNode* node) {
    return (node != nullptr) ? getHeight(node->left) - getHeight(node->right) : 0;
}

// Función para rotar un subárbol a la derecha
AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + std::max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + std::max(getHeight(x->left), getHeight(x->right));

    return x;
}

// Función para rotar un subárbol a la izquierda
AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + std::max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + std::max(getHeight(y->left), getHeight(y->right));

    return y;
}

// Función para insertar una palabra clave en el árbol AVL
AVLNode* insert(AVLNode* root, const std::string& key, int bookIndex) {
    if (root == nullptr) {
        return new AVLNode(key, bookIndex);
    }

    if (key < root->keyword) {
        root->left = insert(root->left, key, bookIndex);
    } else if (key > root->keyword) {
        root->right = insert(root->right, key, bookIndex);
    } else {
        // La palabra clave ya existe, agrega el índice del libro a la lista de libros
        root->books.push_back(bookIndex);
        return root;
    }

    root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));

    // Verifica el equilibrio y realiza rotaciones si es necesario
    int balance = getBalanceFactor(root);

    // Caso izquierda-izquierda
    if (balance > 1 && key < root->left->keyword) {
        return rotateRight(root);
    }

    // Caso derecha-derecha
    if (balance < -1 && key > root->right->keyword) {
        return rotateLeft(root);
    }

    // Caso izquierda-derecha
    if (balance > 1 && key > root->left->keyword) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // Caso derecha-izquierda
    if (balance < -1 && key < root->right->keyword) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

#endif;
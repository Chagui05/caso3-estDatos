#ifndef _AVL_
#define _AVL_ 1
#include <iostream>
#include <algorithm>
#include <vector>
#include "AVLNode.h"
using namespace std;
//ayuda de chatgpt

template <typename T>
class MultisetAVLTree
{
private:
    Node<T> *root;

    int getHeight(Node<T> *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        return node->height;
    }

    int getBalanceFactor(Node<T> *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }

    Node<T> *rotateRight(Node<T> *y)
    {
        Node<T> *x = y->left;
        Node<T> *Z = x->right;

        // Perform rotation
        x->right = y;
        y->left = Z;

        // Update heights
        y->height = 1 + std::max(getHeight(y->left), getHeight(y->right));
        x->height = 1 + std::max(getHeight(x->left), getHeight(x->right));

        return x;
    }

    Node<T> *rotateLeft(Node<T> *x)
    {
        Node<T> *y = x->right;
        Node<T> *Z = y->left;

        // Perform rotation
        y->left = x;
        x->right = Z;

        // Update heights
        x->height = 1 + std::max(getHeight(x->left), getHeight(x->right));
        y->height = 1 + std::max(getHeight(y->left), getHeight(y->right));

        return y;
    }

    Node<T> *insertNode(Node<T> *node, T *data, int pCount)
    {
        if (node == nullptr)
        {
            return new Node<T>(pCount, data);
        }

        // Inserta los nodos duplicados en el subárbol izquierdo
        if (pCount <= node->count)
        {
            node->left = insertNode(node->left, data, pCount);
        }
        else // Inserta los nodos duplicados en el subárbol derecho
        {
            node->right = insertNode(node->right, data, pCount);
        }

        // Update height of current node
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

        // Realiza las rotaciones y ajustes necesarios para mantener el equilibrio del AVL
        int balance = getBalanceFactor(node);

        // Casos de rotación (Left Left, Right Right, Left Right, Right Left) permanecen iguales

        return node;
    }

    void inorderTraversal(Node<T> *node)
    {
        if (node == nullptr)
        {
            return;
        }
        inorderTraversal(node->left);
        std::cout << node->count << " " << node->data << std::endl;
        inorderTraversal(node->right);
    }

    void reverseInOrder(Node<T> *node)
    {
        if (node == nullptr)
        {
            return;
        }
        reverseInOrder(node->right);
        std::cout << node->count << " " << node->data << std::endl;
        reverseInOrder(node->left);
    }

    void reverseInorderVector(Node<T> *node, vector<T *> *dataBunch)
    {
        if (node == nullptr)
        {
            return;
        }
        reverseInorderVector(node->right, dataBunch);
        dataBunch->push_back(node->data);
        reverseInorderVector(node->left, dataBunch);
    }

public:
    MultisetAVLTree() : root(nullptr) {}

    void insert(T *data, int pCount)
    {
        root = insertNode(root, data, pCount);
    }

    void printInorder()
    {
        inorderTraversal(root);
        std::cout << std::endl;
    }

    void printReverseInOrder()
    {
        reverseInOrder(root);
        std::cout << std::endl;
    }
    vector<T *>* topVector()
    {
        vector<T *> *top = new vector<T *>();
        reverseInorderVector(root, top);
        return top;
    }
};

#endif
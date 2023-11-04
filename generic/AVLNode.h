#ifndef _AVLNODE_
#define _AVLNODE_ 1
#include <iostream>
#include <algorithm>

template <typename T>
struct Node
{

    int count;
    T *data;
    Node *left;
    Node *right;
    Node *parent;
    int height;
    
    Node(int value, T *data)
    {
        count = value;
        this->data = data;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        height = 1;
    }
};
#endif
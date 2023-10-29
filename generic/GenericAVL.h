#include <iostream>
#include <algorithm>

template <typename T>
class Node
{
    T *data;
    Node *left;
    Node *right;
    Node *parent;
    int height;

    Node(T *value)
    {
        data = value;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        height = 1;
    }

    T *getData()
    {
        return data;
    }
    void setData(T *value)
    {
        data = value;
    }
    Node *getLeft()
    {
        return left;
    }
    Node *getRight()
    {
        return right;
    }
};

template <typename T>
class AVLTree
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

    Node<T> *insertNode(Node<T> *node, const T &value)
    {
        if (node == nullptr)
        {
            return new Node<T>(value);
        }

        // Insert data
        if (value < node->data)
        {
            node->left = insertNode(node->left, value);
        }
        else if (value > node->data)
        {
            node->right = insertNode(node->right, value);
        }
        else
        {
            // Duplicate values are not allowed
            return node;
        }

        // Update height of current node
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

        // Get the balance factor to check if this node became unbalanced
        int balance = getBalanceFactor(node);

        // Left Left Case
        if (balance > 1 && value < node->left->data)
        {
            return rotateRight(node);
        }

        // Right Right Case
        if (balance < -1 && value > node->right->data)
        {
            return rotateLeft(node);
        }

        // Left Right Case
        if (balance > 1 && value > node->left->data)
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right Left Case
        if (balance < -1 && value < node->right->data)
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    void inorderTraversal(Node<T> *node)
    {
        if (node == nullptr)
        {
            return;
        }
        inorderTraversal(node->left);
        std::cout << node->data << " ";
        inorderTraversal(node->right);
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(const T &value)
    {
        root = insertNode(root, value);
    }

    void printInorder()
    {
        inorderTraversal(root);
        std::cout << std::endl;
    }
};

int main()
{
    return 0;
}

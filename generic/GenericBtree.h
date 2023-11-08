#include <iostream>
#include <vector>
#include <string>
using namespace std;

////////////////////////////// NO USAR ESTE
struct Word {
    string key;
    vector<string> descriptions;
    vector<int> pages;
};

class BTreeNode {
    Word *keys;
    int t;
    BTreeNode **children;
    int n;
    bool leaf;

public:
    BTreeNode(int _t, bool _leaf);

    void insertNonFull(Word word);
    void splitChild(int i, BTreeNode *child);
    void traverse();
    friend class BTree;
};

class BTree {
    BTreeNode *root;
    int degree;

public:
    BTree(int _degree) {
        root = NULL;
        degree = _degree;
    }

    void traverse() {
        if (root != NULL)
            root->traverse();
    }

    void insert(Word word);
};

BTreeNode::BTreeNode(int t, bool leafNode) {
    this->t = t;
    leaf = leafNode;

    keys = new Word[2 * t - 1];
    children = new BTreeNode *[2 * t];

    n = 0;
}

void BTreeNode::traverse() {
    int i;
    for (i = 0; i < n; i++) {
        if (!leaf)
            children[i]->traverse();
        cout << " " << keys[i].key;
    }

    if (!leaf)
        children[i]->traverse();
}

void BTree::insert(Word word) {
    if (root == NULL) {
        root = new BTreeNode(degree, true);
        root->keys[0] = word;
        root->n = 1;
    } else {
        if (root->n == 2 * degree - 1) {
            BTreeNode *newRoot = new BTreeNode(degree, false);

            newRoot->children[0] = root;

            newRoot->splitChild(0, root);

            int i = 0;
            if (newRoot->keys[0].key < word.key)
                i++;
            newRoot->children[i]->insertNonFull(word);

            root = newRoot;
        } else
            root->insertNonFull(word);
    }
}

void BTreeNode::insertNonFull(Word word) {
    int i = n - 1;

    if (leaf) {
        while (i >= 0 && keys[i].key > word.key) {
            keys[i + 1] = keys[i];
            i--;
        }

        keys[i + 1] = word;
        n++;
    } else {
        while (i >= 0 && keys[i].key > word.key)
            i--;

        if (children[i + 1]->n == 2 * t - 1) {
            splitChild(i + 1, children[i + 1]);

            if (keys[i + 1].key < word.key)
                i++;
        }
        children[i + 1]->insertNonFull(word);
    }
}

void BTreeNode::splitChild(int i, BTreeNode *child) {
    BTreeNode *newChild = new BTreeNode(child->t, child->leaf);
    newChild->n = t - 1;

    for (int j = 0; j < t - 1; j++)
        newChild->keys[j] = child->keys[j + t];

    if (!child->leaf) {
        for (int j = 0; j < t; j++)
            newChild->children[j] = child->children[j + t];
    }

    child->n = t - 1;
    for (int j = n; j >= i + 1; j--)
        children[j + 1] = children[j];

    children[i + 1] = newChild;

    for (int j = n - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    keys[i] = child->keys[t - 1];
    n++;
}

int main() {
    BTree bTree(3);
    Word word1 = {"apple", {"fruit"}, {1}};
    Word word2 = {"banana", {"fruit"}, {2}};
    Word word3 = {"orange", {"fruit"}, {3}};
    Word word4 = {"apple", {"color"}, {4}};

    bTree.insert(word1);
    bTree.insert(word2);
    bTree.insert(word3);
    bTree.insert(word4);

    cout << "The B-tree is: ";
    bTree.traverse();
    cout << endl;
    return 0;
}

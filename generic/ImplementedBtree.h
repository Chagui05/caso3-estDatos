#ifndef _FBTREE_
#define _FBTREE_ 1
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int minDegree = 3;
struct Word
{
  string *key;
  vector<string *> *description;
  vector<int *> *pages;

  Word() : key(nullptr), description(new vector<string *>), pages(new vector<int *>) {}
  void setWord(string *pkey, string *pdescription, int *ppages)
  {
    this->key = pkey;
    this->description->push_back(pdescription);
    this->pages->push_back(ppages);
  }
};

class BTreeNode
{
  Word *keys;
  int minDegree;
  BTreeNode **children;
  int numKeys;
  bool isLeaf;

public:
  BTreeNode(int minDeg, bool leafNode);
  void insertNonFull(Word *word);
  void splitChild(int i, BTreeNode *child);
  void traverse();
  BTreeNode *search(string key);

  Word *getKey(string key)
  {
    int index = numKeys;
    for (int i = 0; i < index; ++i)
    {
      if (*keys[i].key == key)
      {
        return &keys[i];
      }
    }
    return nullptr;
  }

  friend class BTree;
};

class BTree
{
  BTreeNode *root;
  int minDegree;

public:
  BTree()
  {
    root = nullptr;
    minDegree = 3;
  }

  BTree(int minDeg)
  {
    root = nullptr;
    minDegree = minDeg;
  }

  void traverse()
  {
    if (root != nullptr)
      root->traverse();
  }

  BTreeNode *search(string word)
  {
    return (root == nullptr) ? nullptr : root->search(word);
  }

  bool isEmpty()
  {
    return root == nullptr;
  }

  void insert(Word *word);
};

BTreeNode::BTreeNode(int minDeg, bool leafNode)
{
  minDegree = minDeg;
  isLeaf = leafNode;

  keys = new Word[2 * minDegree - 1];
  children = new BTreeNode *[2 * minDegree];

  numKeys = 0;
}

void BTreeNode::traverse()
{
  int index;
  for (index = 0; index < numKeys; index++)
  {
    if (!isLeaf)
      children[index]->traverse();
    cout << " " << *keys[index].key;
  }

  if (!isLeaf)
    children[index]->traverse();
}

BTreeNode *BTreeNode::search(string word)
{
  int index = 0;
  while (index < numKeys && word > *keys[index].key)
    index++;

  if (keys[index].key == nullptr)
  {
    return children[index]->search(word);
  } 

  if (*keys[index].key == word)
  {
    return this;
  }
  if (isLeaf)
  {
    return nullptr;
  }
  return children[index]->search(word);
}

void BTree::insert(Word *word)
{
  if (root == nullptr)
  {
    root = new BTreeNode(minDegree, true);
    root->keys[0] = *word;
    root->numKeys = 1;
  }
  else
  {
    if (root->numKeys == 2 * minDegree - 1)
    {
      BTreeNode *newRoot = new BTreeNode(minDegree, false);

      newRoot->children[0] = root;

      newRoot->splitChild(0, root);

      int index = 0;
      if (*newRoot->keys[0].key < *word->key)
        index++;
      newRoot->children[index]->insertNonFull(word);

      root = newRoot;
    }
    else
      root->insertNonFull(word);
  }
}

void BTreeNode::insertNonFull(Word *word)
{
  int index = numKeys - 1;

  if (isLeaf)
  {
    while (index >= 0 && *keys[index].key > *word->key)
    {
      keys[index + 1] = keys[index];
      index--;
    }

    if (index >= 0 && *keys[index].key == *word->key)
    {
      keys[index].description->push_back(word->description->at(0));
      keys[index].pages->push_back(word->pages->at(0));
    }
    else
    {
      // Insert the new word at the correct position
      keys[index + 1] = *word;
      numKeys = numKeys + 1;
    }
  }
  else
  {
    while (index >= 0 && *keys[index].key > *word->key)
    {
      index--;
    }
    if (children[index + 1]->numKeys == 2 * minDegree - 1)
    {
      splitChild(index + 1, children[index + 1]);
      if (*keys[index + 1].key < *word->key)
        index++;
    }
    children[index + 1]->insertNonFull(word);
  }
}

void BTreeNode::splitChild(int i, BTreeNode *child)
{
  BTreeNode *newNode = new BTreeNode(child->minDegree, child->isLeaf);
  newNode->numKeys = minDegree - 1;

  for (int j = 0; j < minDegree - 1; j++)
    newNode->keys[j] = child->keys[j + minDegree];

  if (!child->isLeaf)
  {
    for (int j = 0; j < minDegree; j++)
      newNode->children[j] = child->children[j + minDegree];
  }

  child->numKeys = minDegree - 1;

  for (int j = numKeys; j >= i + 1; j--)
    children[j + 1] = children[j];

  children[i + 1] = newNode;

  for (int j = numKeys - 1; j >= i; j--)
    keys[j + 1] = keys[j];

  keys[i] = child->keys[minDegree - 1];
  numKeys++;
}

/*
  BTree *tree = new BTree(3);

  Word* word1 = new Word();
  string *key1 = new string("zzzz");
  string *description1 = new string("aaaa");
  int *page1 = new int(3);
  word1->setWord(key1, description1, page1);

  Word* word2 = new Word();
  string* word2key = new string("fey");
  string* word2description = new string("description2");
  int* word2page = new int(2);
  word2->setWord(word2key, word2description, word2page);


  Word* word3 = new Word();
  string* word3key = new string("keyyy");
  string* word3description = new string("description3");
  int* word3page = new int(5);
  word3->setWord(word3key, word3description, word3page);

  Word* word4 = new Word();
  string* word4key = new string("aa");
  string* word4description = new string("description4");
  int* word4page = new int(4);
  word4->setWord(word4key, word4description, word4page);

  Word* word5 = new Word();
  string* word5key = new string("bee");
  string* word5description = new string("description5");
  int* word5page = new int(1);
  word5->setWord(word5key, word5description, word5page);

  Word* word6 = new Word();
  string* word6key = new string("aa");
  string* word6description = new string("description6");
  int* word6page = new int(1);
  word6->setWord(word6key, word6description, word6page);

  tree->insert(word1);
  tree->insert(word2);
  tree->insert(word3);
  tree->insert(word4);
  tree->insert(word5);
  tree->insert(word6);
  tree->traverse();

  return 0;
}*/
#endif
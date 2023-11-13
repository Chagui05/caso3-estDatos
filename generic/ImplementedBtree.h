#ifndef _BTREE_
#define _BTREE_ 1
#include <iostream>
#include <vector>
#include <string>
using namespace std;
int minDegreee = 3;

//taken from https://www.programiz.com/dsa/b-tree , but modified for us

struct Word
{
  string* key;
  vector<string*>* description;
  vector<int*>* pages;

  Word() : key(nullptr), description(new vector<string*>), pages(new vector<int*>) {}
  void setWord(string &pkey, string& pdescription, int& ppages)
  {
    this->key = new string(pkey);
    this->description->push_back(new string(pdescription));
    this->pages->push_back(new int(ppages));
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
  BTreeNode(int _minDegree, bool _isLeaf);
  void insertNonFull(Word *word);
  void splitChild(int i, BTreeNode *child);
  void traverse();
  Word* search(string *key);
  Word* findKey(string key);
  friend class BTree;
};



class BTree
{
  BTreeNode *root;
  int minDegree;

public:
  BTree()
  {
    root = NULL;
    minDegree = minDegreee;
  }
  BTree(int _minDegree)
  {
    root = NULL;
    minDegree = _minDegree;
  }

  void traverse()
  {
    if (root != NULL)
      root->traverse();
  }

  Word* search(string *key)
  {
    if (root != nullptr)
    {
      return root->search(key);
    }
    else
    {
      Word* notFound = new Word();
      string* noFound = new string("Key not found");
      notFound->key = noFound;
      return notFound;
    }
  }
  void insert(Word* word);
  
};



BTreeNode::BTreeNode(int _minDegree, bool _isLeaf)
{
  minDegree = _minDegree;
  isLeaf = _isLeaf;

  keys = new Word[2 * minDegree - 1];
  children = new BTreeNode *[2 * minDegree];

  numKeys = 0;
}

void BTreeNode::traverse()
{
  int i;
  for (i = 0; i < numKeys; i++)
  {
    if (!isLeaf)
      children[i]->traverse();
    cout << " " << *keys[i].key<<endl;
  }

  if (!isLeaf)
    children[i]->traverse();
}
void BTreeNode::insertNonFull(Word* word)
{
  int i = numKeys - 1;

  if (isLeaf)
  {
    while (i >= 0 && keys[i].key > word->key)
    {
      keys[i + 1] = keys[i];
      i--;
      if (word->key == keys[i].key)
      {

        keys[i].description->push_back(word->description->at(0));
        keys[i].pages->push_back(word->pages->at(0));
        return;
      }
    }
    if (word->key == keys[i].key)
      {
        
        keys[i].description->push_back(word->description->at(0));
        keys[i].pages->push_back(word->pages->at(0));
        return;
      }
    keys[i + 1] = *word;
    numKeys++;
  }
  else
  {
    while (i >= 0 && keys[i].key > word->key)
      i--;

    if (children[i + 1]->numKeys == 2 * minDegree - 1)
    {

      splitChild(i + 1, children[i + 1]);

      if (keys[i + 1].key < word->key)
        i++;
    }
    children[i + 1]->insertNonFull(word);
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

Word* BTreeNode::search(string *key)
{
  int i = 0;
  while (i < numKeys && key > keys[i].key)
  {
    i++;
  }

  if (i < numKeys && key == keys[i].key)
  {
    return &keys[i];
  }
  else if (isLeaf)
  {
    Word* notFound = new Word();
    string* noFound = new string("Key not found") ;
    notFound->key = noFound;
    return notFound;
  }
  else
  {
    return children[i]->search(key);
  }
}

void BTree::insert(Word *word)
{
  if (root == NULL)
  {
    root = new BTreeNode(minDegree, true);
    root->keys[0] = *word;
    root->numKeys = 1;
  }
  else
  {
    if (root->numKeys == 2 * minDegree - 1)
    {
      BTreeNode *s = new BTreeNode(minDegree, false);
      s->children[0] = root;
      s->splitChild(0, root);

      int i = 0;
      if (s->keys[0].key < word->key)
        i++;
      s->children[i]->insertNonFull(word);
      root = s;
    }
    else
    {
      root->insertNonFull(word);
    }
  }
}

class PruebaBtree
{
private:
  BTree* WordParragraphBTree;    
public:

PruebaBtree()
{
  WordParragraphBTree = new BTree();
}

void generateBtree()
{
  for(int i = 0; i < 5000; i++ )
  {
    string* key = new string("key" + to_string(i));
    string* description = new string("description" + to_string(i));
    int* page = new int(i);
    Word* word = new Word();
    word->setWord(*key, *description, *page);
    WordParragraphBTree->insert(word);
  }
  
}
void printBT()
{
  WordParragraphBTree->traverse();
}

BTree* getBTree()
{
  return WordParragraphBTree;
}
};

// int main()
// {
//   PruebaBtree prueba;

//   prueba.generateBtree();
//   prueba.getBTree()->traverse();

//   return 0;
// }
#endif
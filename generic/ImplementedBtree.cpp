#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Word
{
  string key;
  vector<string> description;
  vector<int> pages;
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
  void insertNonFull(Word word);
  void splitChild(int i, BTreeNode *child);
  void traverse();
  Word search(string key);
  friend class BTree;
};

class BTree
{
  BTreeNode *root;
  int minDegree;

public:
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

  Word search(string key)
  {
    if (root != nullptr)
    {
      return root->search(key);
    }
    else
    {
      Word notFound;
      notFound.key = "Key not found";
      return notFound;
    }
  }

  void insert(Word word);
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
    cout << " " << keys[i].key;
  }

  if (!isLeaf)
    children[i]->traverse();
}

void BTreeNode::insertNonFull(Word word)
{
  int i = numKeys - 1;

  if (isLeaf)
  {
    while (i >= 0 && keys[i].key > word.key)
    {
      keys[i + 1] = keys[i];
      i--;
      if (word.key == keys[i].key)
      {
        keys[i].description.push_back(word.description[0]);
        keys[i].pages.push_back(word.pages[0]);
        return;
      }
    }
    if (word.key == keys[i].key)
      {
        keys[i].description.push_back(word.description[0]);
        keys[i].pages.push_back(word.pages[0]);
        return;
      }
    keys[i + 1] = word;
    numKeys++;
  }
  else
  {
    while (i >= 0 && keys[i].key > word.key)
      i--;
    if (word.key == keys[i].key)
    {
      keys[i].description.push_back(word.description[0]);
      keys[i].pages.push_back(word.pages[0]);
      return;
    }

    if (children[i + 1]->numKeys == 2 * minDegree - 1)
    {
      splitChild(i + 1, children[i + 1]);

      if (keys[i + 1].key < word.key)
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

Word BTreeNode::search(string key)
{
  int i = 0;
  while (i < numKeys && key > keys[i].key)
  {
    i++;
  }

  if (i < numKeys && key == keys[i].key)
  {
    return keys[i];
  }
  else if (isLeaf)
  {
    Word notFound;
    notFound.key = "Key not found";
    return notFound;
  }
  else
  {
    return children[i]->search(key);
  }
}

void BTree::insert(Word word)
{
  if (root == NULL)
  {
    root = new BTreeNode(minDegree, true);
    root->keys[0] = word;
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
      if (s->keys[0].key < word.key)
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

int main()
{
  BTree t(3);
  Word word1 = {"apple", {"fruit"}, {1, 2, 3}};
  Word word2 = {"orange", {"fruit"}, {4, 5, 6}};
  Word word3 = {"banana", {"fruit"}, {7, 8, 9}};
  Word word33 = {"lemon", {"fruta"}, {4}};
  Word word44 = {"pitaya", {"fruta"}, {9000}};
  Word word4 = {"apple", {"fruta1"}, {5}};
  Word word5 = {"apple", {"fruta2"}, {6}};
  Word word6 = {"apple", {"fruta3"}, {7}};
  Word word7 = {"apple", {"fruta4"}, {8}};
  Word word8 = {"apple", {"fruta5"}, {9}};
  Word word9 = {"apple", {"fruta6"}, {10}};
  Word word10 = {"pinna", {"fruta7"}, {11}};
  Word word11 = {"yanose", {"fruta8"}, {12}};
  Word word12 = {"yano", {"fruta9"}, {13}};
  Word word13 = {"pinna", {"fruta10"}, {14}};
  Word word14 = {"apple", {"aaaa"}, {1222}};
  Word word45 = {"pitaya", {"1111"}, {1111}};
  

  t.insert(word1);
  t.insert(word2);
  t.insert(word3);
  t.insert(word33);
  t.insert(word44);
  t.insert(word4);
  t.insert(word5);
  t.insert(word6);
  t.insert(word7);
  t.insert(word8);
  t.insert(word9);
  t.insert(word10);
  t.insert(word11);
  t.insert(word12);
  t.insert(word13);
  t.insert(word14);
  t.insert(word45);



  t.traverse();
  cout << endl;

  string searchKey = "lemon";
  Word result = t.search(searchKey);

  if (result.key != "Key not found")
  {
    cout << "Key found: " << result.key << endl;
    cout << "Description: ";
    for (const auto &desc : result.description)
    {
      cout << desc << " ";
    }
    cout << endl;
    cout << "Pages: ";
    for (const auto &page : result.pages)
    {
      cout << page << " ";
    }
    cout << endl;
  }
  else
  {
    cout << "Key not found" << endl;
  }

  return 0;
}

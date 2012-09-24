#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;

struct Tree {
  int Value;
  Tree *Left;
  Tree *Right;
};

Tree *NewNode(int i) {
  Tree *t = new Tree;
  t->Value = i;
  t->Left = nullptr;
  t->Right = nullptr;
  return t;
}

class BinaryTree {

public:
  BinaryTree();
  void Add(int);
  vector<int> Walk();
  unsigned int Levels() const;

private:
  unsigned levels;
  Tree *root;
  void add(int i, Tree* &leaf);
  vector<int> walk(Tree *leaf, vector<int>&);
};

BinaryTree::BinaryTree()
  : root(nullptr), levels(0) {}

unsigned int BinaryTree::Levels() const {
  return levels;
}

void BinaryTree::Add(int i) {

  levels++;

  if (root == nullptr) {
    root = NewNode(i);
    return;
  }

  if (root->Value < i) {
    return add(i, root->Right);
  }
  add(i, root->Left);
  return;
}

void BinaryTree::add(int i, Tree* &leaf) {
  if (leaf == nullptr) {
    leaf = NewNode(i);
    return;
  }
  if (leaf->Value < i) {
    return add(i, leaf->Right);
  }
  return add(i, leaf->Left);
}

vector<int> BinaryTree::Walk() {

  vector<int> out;
  if (root == nullptr) {
    return out;
  }

  walk(root->Left, out);
  out.push_back(root->Value);
  walk(root->Right, out);

  return out;
}

vector<int> BinaryTree::walk(Tree *leaf, vector<int>& out) {
  if (leaf == nullptr) {
    return out;
  }

  walk(leaf->Left, out);
  out.push_back(leaf->Value);
  walk(leaf->Right, out);

  return out;
}

int main() {
  BinaryTree btree;
  vector<int> tree;

  btree.Add(0);
  btree.Add(4);
  btree.Add(5);
  btree.Add(-2);
  btree.Add(-1);
  btree.Add(8);

  tree = btree.Walk();

  for (auto x = tree.begin(); x != tree.end(); ++x) {
    cout << (*x) << "\n";
  }
}

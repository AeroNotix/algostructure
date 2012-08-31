#include <iostream>
#include <vector>
#include <stdio.h>

struct Tree {
  int Value;
  Tree *Left;
  Tree *Right;
};

class BinaryTree {

public:
  BinaryTree();
  void Add(int);
  std::vector<int> Walk();

private:
  Tree *root;
  void add(int i, Tree *leaf);
  std::vector<int> walk(Tree *leaf);
};

BinaryTree::BinaryTree( ) {
  root = NULL;
}

void BinaryTree::Add(int i) {
  if (root == NULL) {
	root = new Tree;
	root->Value=i;
	return;
  }

  if (root->Value < i) {
	return add(i, root->Right);
  }
  add(i, root->Left);
  return;
}

void BinaryTree::add(int i, Tree *leaf) {
  if (leaf == NULL) {
	leaf = new Tree;
	leaf->Value = i;
	return;
  }
  if (leaf->Value < i) {
	return add(i, leaf->Right);
  }
  return add(i, leaf->Left);
}

std::vector<int> BinaryTree::Walk() {

  std::vector<int> out;
  if (root == NULL) { 
	return out;
  }
  std::vector<int> right;
  std::vector<int>::const_iterator x;
  right = walk(root->Right);
  for (x=right.begin();x!=right.end();++x) {
	out.push_back((*x));
  }
  out.push_back(root->Value);
  std::vector<int> left;
  left = walk(root->Left);
  for (x=left.begin();x!=left.end();++x) {
	out.push_back((*x));
  }
  return out;
}

std::vector<int> BinaryTree::walk(Tree *leaf) {
  std::vector<int> out;
  if (leaf == NULL) { 
	return out;
  }

  std::vector<int> right;
  std::vector<int>::const_iterator x;
  right = walk(leaf->Right);
  for (x=right.begin();x!=right.end();++x) {
	out.push_back((*x));
  }
  out.push_back(leaf->Value);
  std::vector<int> left;
  left = walk(leaf->Left);
  for (x=left.begin();x!=left.end();++x) {
	out.push_back((*x));
  }
  return out;
}

int main() {
  BinaryTree btree;
  btree.Add(5);
  btree.Add(-1);
  btree.Add(3);
  btree.Add(4);
  std::vector<int> tree;
  std::vector<int>::const_iterator x;
  tree = btree.Walk();
  for (x=tree.begin();x!=tree.end();++x) {
	std::cout << (*x) << "\n";
  }
}

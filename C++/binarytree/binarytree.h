#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;

template <class T>
class Tree {
public:
	~Tree();
	T Value;
	Tree<T> *Left;
	Tree<T> *Right;
};

template <class T>
Tree<T>::~Tree() {
	delete Left;
	delete Right;
}


template <class T>
Tree<T> *NewNode(T i) {
	Tree<T> *t = new Tree<T>;
	t->Value = i;
	t->Left = nullptr;
	t->Right = nullptr;
	return t;
}

template <class T>
class BinaryTree {

public:
	BinaryTree();
	~BinaryTree();
	void Add(T);
	vector<T> Walk();
	unsigned int Levels() const;

private:
	unsigned int levels;
	Tree<T> *root;
	void add(T i, Tree<T>* &leaf);
	vector<T> walk(Tree<T> *leaf, vector<T>&);
};

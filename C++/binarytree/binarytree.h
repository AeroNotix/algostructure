#include <iostream>
#include <vector>
#include <stdio.h>
#include <Python.h>

using namespace std;

namespace binarytree {

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

	template <class T>
		BinaryTree<T>::BinaryTree()
		: root(nullptr), levels(0) {}

	template <class T>
		BinaryTree<T>::~BinaryTree() {
		delete root;
	}

	template <class T>
		unsigned int BinaryTree<T>::Levels() const {
		return levels;
	}

	template <class T>
		void BinaryTree<T>::Add(T i) {

		levels++;

		if (root == nullptr) {
			root = NewNode<T>(i);
			return;
		}

		if (root->Value < i) {
			return add(i, root->Right);
		}
		add(i, root->Left);
		return;
	}

	template <class T>
		void BinaryTree<T>::add(T i, Tree<T>* &leaf) {
		if (leaf == nullptr) {
			leaf = NewNode<T>(i);
			return;
		}
		if (leaf->Value < i) {
			return add(i, leaf->Right);
		}
		return add(i, leaf->Left);
	}

	template <class T>
		vector<T> BinaryTree<T>::Walk() {

		vector<T> out;
		if (root == nullptr) {
			cout << "here\n";
			return out;
		}

		walk(root->Left, out);
		out.push_back(root->Value);
		walk(root->Right, out);

		return out;
	}

	template <class T>
		vector<T> BinaryTree<T>::walk(Tree<T> *leaf, vector<T>& out) {
		if (leaf == nullptr) {
			return out;
		}

		walk(leaf->Left, out);
		out.push_back(leaf->Value);
		walk(leaf->Right, out);

		return out;
	}
}

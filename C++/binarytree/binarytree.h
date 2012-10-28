#include <stdio.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <stdexcept>

namespace binarytree {

    template <class T>
    class Tree {
    public:
		Tree()
			: Value(T()), Left(nullptr), Right(nullptr) {};
		Tree(T el)
			: Value(el), Left(nullptr), Right(nullptr) {};
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
    class BinaryTree {
    public:
		BinaryTree()
			: pre(nullptr), fcn(nullptr), root(nullptr), levels(0) {}
		BinaryTree(bool (*f)(T, T), void(*f2)(T))
			: pre(f2), fcn(f), root(nullptr), levels(0) {}
		~BinaryTree();
		void Add(T);
		std::vector<T> Walk() const;
		unsigned int Levels() const;
		std::string ToString() const;
		bool (*fcn)(T, T);
		void (*pre)(T);

    private:
		unsigned int levels;
		Tree<T> *root;
		void add(T i, Tree<T>* &leaf);
		void walk(Tree<T> *leaf, std::vector<T>*) const;
    };

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

		if (pre != nullptr)
			pre(i);

		levels++;
		Tree<T> **node = &(this->root);
		while (*node != nullptr) {
			if (fcn != nullptr) {
				if (fcn((*node)->Value, i)) {
					node = &((*node)->Left);
				} else {
					node = &((*node)->Right);
				}
			} else {
				if ((*node)->Value > i) {
					node = &((*node)->Left);
				} else {
					node = &((*node)->Right);
				}
			}
		}
		*node = new Tree<T>(i);
	}

    template <class T>
    std::vector<T> BinaryTree<T>::Walk() const {
		std::vector<T> out;
		if (root == nullptr) {
			return out;
		}

		walk(root->Left, &out);
		out.push_back(root->Value);
		walk(root->Right, &out);

		return out;
    }

    template <class T>
    void BinaryTree<T>::walk(Tree<T> *leaf, std::vector<T> *out) const {
		if (leaf == nullptr) {
			return;
		}

		walk(leaf->Left, out);
		out->push_back(leaf->Value);
		walk(leaf->Right, out);
    }

    template<>
    std::string BinaryTree<int>::ToString() const {
		std::stringstream buffer(std::stringstream::in);
		buffer << "[ ";
		for (auto el : Walk()) {
			buffer << el << " ";
		}
		buffer << "]";
		return buffer.str();
    }
}

#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>

template <class T>
class Node {

private:
    typedef typename T::iterator iter;
    typedef T holding_type;

    T prefix;
    std::vector<Node<T>> Nodes;
    void Insert(iter a, iter b);
    int DifferAt(T b);
    int DifferAt(iter beg, iter end);
    void Walk(std::vector<T> &out);
    int levels = 0;

public:
    Node() {};
    explicit Node(T pre) : prefix(pre) {};

    int Levels() const { return levels; };
    void Insert(T a);
    std::vector<T> Walk();

};

template <class T>
int Node<T>::DifferAt(T b) {

    T cmp;
    if (prefix.size() < b.size()) {
	cmp = prefix;
    } else {
	cmp = b;
    }

    int idx = 0;
    for (; idx<cmp.size(); ++idx) {
	if (prefix[idx] != b[idx]) {
	    break;
	}
    }

    return idx;
}

template <class T>
int Node<T>::DifferAt(Node<T>::iter beg, Node<T>::iter end) {
    auto nodebeg = prefix.begin();
    int i = 0;
    for (; nodebeg != prefix.end(); ++nodebeg) {
	if (*beg == *nodebeg) {
	    ++beg;
	    ++i;
	    continue;
	}
	break;
    }
    return i;
}

template <class T>
void Node<T>::Insert(T newitem) {
    ++levels;
    Insert(newitem.begin(), newitem.end());
}

template <class T>
void Node<T>::Insert(Node<T>::iter beg, Node<T>::iter end) {

    if (beg == end) {
	return;
    }

    for (auto nbeg = Nodes.begin(); nbeg != Nodes.end(); ++nbeg) {
	int differ = nbeg->DifferAt(beg+prefix.size(), end);
	if (differ > 0) {
	    nbeg->Insert(beg+prefix.size()+differ, end);
	    return;
	}
    }

    Nodes.push_back(Node<T>(T(beg+DifferAt(beg, end), end)));
}

template <class T>
std::vector<T> Node<T>::Walk() {
    std::vector<T> out;
    out.push_back(prefix);

    for (auto nbeg = Nodes.begin(); nbeg != Nodes.end(); ++nbeg) {
	nbeg->Walk(out);
    }

    return out;
}

template <class T>
void Node<T>::Walk(std::vector<T> &out) {
    out.push_back(prefix);

    for (auto beg = Nodes.begin(); beg != Nodes.end(); ++beg) {
	beg->Walk(out);
    }
}

void PrintVec(std::vector<int> vec) {
    std::cout << "[ ";
    for (auto b = vec.begin(); b != vec.end(); ++b) {
	std::cout << *b;
    }
    std::cout << " ]" << std::endl;
}

int main() {

    Node<std::string> n;

    n.Insert("HIIIII");
    n.Insert("HIIIIIa");
    n.Insert("HIIIIIaa");
    n.Insert("HIIIIIaaa");
    n.Insert("HIIIIIaaaa");
    n.Insert("something");

    auto t = n.Walk();
    for (auto b = t.begin(); b != t.end(); ++b) {
	std::cout << *b << std::endl;
    }

    std::cout << n.Levels() << std::endl;

    Node<std::vector<int>> vtrie;

    vtrie.Insert({1,2,3,4,5});
    vtrie.Insert({1,3,4,5,6});
    vtrie.Insert({1,3,4,55,6});

    std::vector<std::vector<int>> watr(vtrie.Walk());

    for (auto b = watr.begin(); b != watr.end(); ++b) {
	PrintVec(*b);
    }
    return 0;
}

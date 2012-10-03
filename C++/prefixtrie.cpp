#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
#include <fstream>

template <class T>
class Node {

private:
    typedef typename T::iterator iter;
    typedef typename T::difference_type difftype;

    T prefix;
    int levels = 0;

    void Insert(iter a, iter b);
    void Walk(std::vector<T> &out);
    void Display(int);
    std::vector<Node<T> > Nodes;
    T DifferAt(iter beg);

public:
    int Levels() const { return levels; };

    Node() {};
    explicit Node(T pre) :
	prefix(pre) {};

    Node(T pre, Node<T> n) :
	prefix(pre) {
	Nodes.push_back(n);
    }

    Node<T>& operator=(const Node<T>& rhs);

    void Display();
    void Insert(T a);
    std::vector<T> Walk();

};

template <class T>
Node<T>& Node<T>::operator=(const Node<T>& rhs) {
    prefix = rhs.prefix;
    Nodes = rhs.Nodes;
    return *this;
}

template <class T>
T Node<T>::DifferAt(Node<T>::iter beg) {
    auto nodebeg = prefix.begin();
    auto storeend = prefix.end();

    auto storebeg = beg;

    for (; (nodebeg != storeend) && (*beg == *nodebeg); ++nodebeg ) {
	++beg;
    }
    return T(storebeg, beg);
}

template <class T>
void Node<T>::Insert(T newitem) {
    ++levels;
    Insert(newitem.begin(), newitem.end());
}

template <class T>
void Node<T>::Insert(Node<T>::iter beg, Node<T>::iter end) {

    for (auto nbeg = Nodes.begin(); nbeg != Nodes.end(); ++nbeg) {
	
	auto sub = nbeg->DifferAt(beg);
	if (sub.size() > 0) {
	    if (sub == nbeg->prefix) {
		nbeg->Insert(beg+sub.size(),end);
		return;
	    }

	    nbeg->prefix = T(nbeg->prefix.begin(),
			     nbeg->prefix.begin()+sub.size());

	    *nbeg = Node<T>(T(beg,beg+sub.size()), *nbeg);

	    nbeg->Insert(beg,end);
	    return;
	}
    }

    Nodes.push_back(Node<T>(T(beg,end)));
}

template <class T>
std::vector<T> Node<T>::Walk() {
    std::vector<T> out;
    out.push_back(prefix);

    for (auto beg = Nodes.begin(); beg != Nodes.end(); ++beg) {
	beg->Walk(out);
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

template <class T>
void Node<T>::Display() {

    std::cout << "Prefix tree: " << prefix << std::endl;
    for (auto b = Nodes.begin(); b != Nodes.end(); ++b) {
	b->Display(1);
    }
}

template <class T>
void Node<T>::Display(int level) {
    std::cout << std::string(level, '\t') << prefix << std::endl;
    for (auto b = Nodes.begin(); b != Nodes.end(); ++b) {
	b->Display(level+1);
    }
}

int main(int argc, char* argv[]) {

    if (argc < 2) {
	std::cout << "Please supply a file" << std::endl;
    }

    Node<std::string> n;

    std::ifstream infile(argv[1], std::ifstream::in);

    while (!infile.eof()) {
	std::string s;
	std::getline(infile, s);
	n.Insert(s);
    }

    n.Display();
    return 0;
}


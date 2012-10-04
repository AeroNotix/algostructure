#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iterator>

template <class T>
class Node {

private:
    typedef typename T::const_iterator iter;
    typedef typename T::difference_type difftype;

    T prefix;

    void Insert(iter a, iter b);
    void Walk(std::vector<T> &out);
    void Display(int);
    std::vector<Node<T> > Nodes;
    typename T::difference_type DifferAt(iter beg);

public:
    Node() {};
    explicit Node(const T &pre) :
	prefix(pre) {
	Nodes.reserve(26);
    };

    Node(T pre, const Node<T> &n) :
	prefix(pre) {
	Nodes.reserve(26);
	Nodes.push_back(n);
    }

    Node(iter a, iter b) :
	prefix(a,b) {};

    Node<T>& operator=(const Node<T>& rhs);

    void Display();
    void Insert(const T &a);
    std::vector<T> Walk();

};

template <class T>
Node<T>& Node<T>::operator=(const Node<T>& rhs) {
    prefix = rhs.prefix;
    Nodes = rhs.Nodes;
    return *this;
}

template <class T>
typename T::difference_type Node<T>::DifferAt(Node<T>::iter beg) {
    auto nodebeg = prefix.begin();
    auto storeend = prefix.end();
    auto storebeg = beg;

    for (; (nodebeg != storeend) && (*beg == *nodebeg); ++nodebeg ) {
	++beg;
    }
    return std::distance(storebeg, beg);
}

template <class T>
void Node<T>::Insert(const T &newitem) {
    Insert(newitem.begin(), newitem.end());
}

template <class T>
void Node<T>::Insert(Node<T>::iter beg, Node<T>::iter end) {

    for (auto nbeg = Nodes.begin(); nbeg != Nodes.end(); ++nbeg) {
	auto sub = nbeg->DifferAt(beg);
	if (std::distance(beg,beg+sub) > 0) {
	    if (T(beg,beg+sub) == nbeg->prefix) {
		nbeg->Insert(beg+sub,end);
		return;
	    }

	    nbeg->prefix = T(nbeg->prefix.begin(),
			     nbeg->prefix.begin()+sub);

	    *nbeg = Node<T>(T(beg,beg+sub), *nbeg);
	    nbeg->Insert(beg,end);
	    return;
	}
    }

    Nodes.push_back(Node<T>(beg,end));
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

    return 0;
}


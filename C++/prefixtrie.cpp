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

    void Insert(iter a, iter b);
    void Walk(std::vector<T> &out);
    void Display(int) const;
    void Display(void (*fcn) (Node<T>), int level);
    typename T::difference_type DifferAt(iter beg);

public:
    Node() {};
    explicit Node(const T &pre) :
	prefix(pre) {};

    explicit Node(T &pre, const Node<T> &n) :
	prefix(pre), Nodes(1,n) {};

    explicit Node(iter a, iter b) :
	prefix(a,b) {};

    const Node<T>& operator=(const Node<T>& rhs) {
	this->prefix = rhs.prefix;
	this->Nodes = rhs.Nodes;
	return *this;
    }

    void Display() const;
    void Display(void (*fcn) (Node<T>));
    void Insert(const T &a);
    std::vector<T> Walk();

    T prefix;
    std::vector<Node<T> > Nodes;

};

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

	T ssub = T(beg,beg+sub);
	if (ssub.size() > 0) {
	    if (ssub == nbeg->prefix) {
		nbeg->Insert(beg+sub,end);
		return;
	    }
	    nbeg->prefix = T(nbeg->prefix.begin()+sub,nbeg->prefix.end());
	    *nbeg = Node<T>(ssub, *nbeg);
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
void Node<T>::Display() const {

    std::cout << "Prefix tree: " << prefix << std::endl;
    for (auto b = Nodes.begin(); b != Nodes.end(); ++b) {
	b->Display(1);
    }
}

template <class T>
void Node<T>::Display(int level) const {
    std::cout << std::string(level, '\t') << prefix << std::endl;
    for (auto b = Nodes.begin(); b != Nodes.end(); ++b) {
	b->Display(level+1);
    }
}

template <class T>
void Node<T>::Display(void (*fcn) (Node<T>)) {
    std::cout << "Prefix tree: ";
    fcn(*this);
    std::cout << std::endl;

    for (auto seg : Nodes)
	seg.Display(fcn, 1);
}

template <class T>
void Node<T>::Display(void (*fcn) (Node<T>), int level) {
    std::cout << std::string(level, '\t');
    std::cout << ".";
    fcn(*this);
    std::cout << std::endl;
    for (auto seg : Nodes)
	seg.Display(fcn, level+1);
}

int main(int argc, char* argv[]) {

    Node<std::string> n;

    if (argc < 2) {
	std::cout << "Please supply a file" << std::endl;
    }

    std::ifstream infile(argv[1], std::ifstream::in);

    std::string s;
    while (!infile.eof()) {
	std::getline(infile, s);
	n.Insert(s);
    }

    return 0;
}

#ifndef PREFIXINC
#include <prefixtrie.h>
#include <fstream>
#define PREFIXINC
#endif

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
    if (argc < 2) {
	std::cout << "Please supply a file" << std::endl;
	return -1;
    }

    std::fstream fs(argv[1], std::fstream::in);
    Node<std::string> n;
    while (fs) {
	std::string s;
	fs >> s;
	n.Insert(s);
    }
}

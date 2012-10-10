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

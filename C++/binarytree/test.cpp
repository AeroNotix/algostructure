#include "binarytree.h"
#include <stdlib.h>
#include <fstream>

int main(int argc, char* argv[]) {
    binarytree::BinaryTree<int> n;
    for (int x = 0; x < 1000000; ++x) {
	n.Add(rand() % 1000000);
    }
    n.Walk();
    /*
    if (argc < 2)
	return 0;

    binarytree::BinaryTree<std::string> n2;
    std::fstream fs(argv[2], std::fstream::in);
    while (!fs.eof()) {
	std::string s;
	getline(fs,s);
	n2.Add(s);
    }
    n2.Walk();
    */
}

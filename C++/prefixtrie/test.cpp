#include <stdlib.h>
#include <string>
#include <fstream>
#include <iostream>
#include "prefixtrie.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
	std::cout << "Please supply a file" << std::endl;
	return -1;
    }

    std::fstream fs(argv[1], std::fstream::in);
    prefixtrie::Node<std::string> n;
    while (!fs.eof()) {
	std::string s;
	std::getline(fs, s);
	n.Insert(s);	
    }
}

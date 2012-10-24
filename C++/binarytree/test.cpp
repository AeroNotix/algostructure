#include "binarytree.h"
#include <stdlib.h>

int main() {
    binarytree::BinaryTree<int> n;
    for (int x = 0; x < 1000000; ++x) {
	n.Add(rand() % 1000000);
    }
    n.Walk();
}

import binarytree
import random

x = binarytree.BinaryTree()
for i in range(259):
    x.add(i)

print x.walk()

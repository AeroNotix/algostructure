import binarytree
import random

x = binarytree.BinaryTree()
for i in range(500000):
    x.add(random.randint(-10000,i+1))

print x.walk()

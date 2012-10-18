import binarytree
import random

def f():
    x = binarytree.BinaryTree()
    for i in range(10):
        x.add(random.randint(0,i))


x = binarytree.BinaryTree()
for i in range(100):
    x.add(random.randint(0,i))

print x.walk()

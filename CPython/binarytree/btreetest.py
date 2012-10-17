import binarytree
import random

def f():
    x = binarytree.BinaryTree()
    for i in range(100000):
        x.add(random.randint(0,i))


#=== Create and Add ===
x = binarytree.BinaryTree()
x.add(-1)
x.add(23)
x.add(2)
print x.walk()

#=== destructor test ==
f() 
raw_input("Hello")


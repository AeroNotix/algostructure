import random
import sys
import time
import binarytree

sys.setrecursionlimit(2000000)

class BinaryTree(object):

    def __init__(self):
        self.value = None
        self.left = None
        self.right = None

    def add(self, element):
        if not self.value:
            self.left = BinaryTree()
            self.right = BinaryTree()
            self.value = element
            return

        if element > self.value:
            return self.right.add(element)
        return self.left.add(element)
    
    def walk(self, li=None):
        if li is None:
            li = []
        if not self.value:
            return li
        if self.left:
            self.left.walk(li)
        li.append(self.value)
        if self.right:
            self.right.walk(li)
        return li

purepython = BinaryTree()
wrapper = binarytree.BinaryTree()

els = []
for x in range(500000):
    els.append(random.randint(1,1000))
'''
t1 = time.clock()
for el in els:
    purepython.add(el)
print time.clock() - t1
'''
t2 = time.clock()
for el in els:
    wrapper.add(el)
print time.clock() - t2

print purepython.walk() == wrapper.walk()

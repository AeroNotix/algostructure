import random
import time
import binarytree

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

        if element < self.value:
            self.right.add(element)
            return
        if element > self.value:
            self.left.add(element)
            return
    
    def walk(self):
        if not self.value:
            return
        if self.left:
            self.left.walk()
        print self.value
        if self.right:
            self.right.walk()

purepython = BinaryTree()
wrapper = binarytree.BinaryTree()

els = []
for x in range(100):
    els.append(random.randint(x,x))
'''
t1 = time.clock()
for el in els:
    purepython.add(el)
print time.clock() - t1
'''
t2 = time.clock()
wrapper.add(0)
for el in els:
    wrapper.add(el)
print time.clock() - t2

li = wrapper.walk()
li.sort()
print li

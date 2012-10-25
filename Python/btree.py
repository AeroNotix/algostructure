import random
import sys

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

if __name__ == '__main__':
    purepython = BinaryTree()
    for x in range(1000000):
        purepython.add(random.randint(1,x+1))

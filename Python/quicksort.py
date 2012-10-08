import random
import sys

sys.setrecursionlimit(20000000)

def quicksort(vec):
    if len(vec) <= 1:
        return vec

    middlepos = len(vec) / 2
    middle = vec[middlepos]

    lesser = []
    greater = []

    vec.pop(middlepos)

    for el in vec:
        if el <= middle:
            lesser.append(el)
            continue
        greater.append(el)

    return quicksort(lesser)+[middle]+quicksort(greater)

if __name__ == '__main__':
    vec = []
    for x in range(1000000):
        vec.append(random.randint(0,x))
    
    quicksort(vec)

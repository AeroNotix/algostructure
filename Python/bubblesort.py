import random
import sys

def bubblesort(vec):
    sys.setrecursionlimit(len(vec))
    idx = 2
    swapped = False
    while (idx < len(vec)):
        if (vec[idx-1] > vec[idx]):
            vec[idx-1], vec[idx] = vec[idx], vec[idx-1]
            swapped = True
        idx += 1
    if swapped:
        bubblesort(vec)

if __name__ == '__main__':
    vec = []
    for x in range(1000):
        vec.append(random.randint(0,x))
    
    bubblesort(vec)
    print vec

    

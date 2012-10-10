
import random
import quicksort

li = []
for x in range(1000000):
    random.randint(0,x)
    li.append(x)

quicksort.sort(li)

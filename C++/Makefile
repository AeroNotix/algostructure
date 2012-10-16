shared:
	g++ -fPIC -shared -std=c++11 -o libprefixtrie.so -Iprefixtrie -O3 prefixtrie/prefixtrie.cpp
	g++ -fPIC -shared -std=c++11 -o libbtree.so -Ibinarytree -O3 binarytree/binarytree.h
	g++ -fPIC -shared -std=c++11 -o libsort.so -Isorting -O3 sorting/quicksort.h sorting/selection.h sorting/bubblesort.h

static:
	g++ -c -std=c++11 -O3 -Iprefixtrie prefixtrie/prefixtrie.cpp
	g++ -c -std=c++11 -O3 -Ibinarytree binarytree/binarytree.cpp
	ar rcs libprefixtrie.a prefixtrie.o
	ar rcs libbinarytree.a binarytree.o
	rm prefixtrie.o
	rm binarytree.o

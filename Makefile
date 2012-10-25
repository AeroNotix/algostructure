timer = /usr/bin/time -f "%e - %M" -a -o results
dict = ~/dev/testing/dictionaries.txt

all:
	g++ -std=c++11 -o C++/bintreetest -O3 -LC++ C++/binarytree/test.cpp
	g++ -std=c++11 -o C++/prefixtrietest -O3 -LC++ C++/prefixtrie/test.cpp
	cd CPython/binarytree; make
	cd CPython/prefixtrie; make

test:
	make

	echo "C++/binarytree" > results
	$(timer) ./C++/bintreetest
	$(timer) ./C++/bintreetest
	$(timer) ./C++/bintreetest
	$(timer) ./C++/bintreetest
	$(timer) ./C++/bintreetest
	$(timer) ./C++/bintreetest
	$(timer) ./C++/bintreetest
	$(timer) ./C++/bintreetest
	$(timer) ./C++/bintreetest
	$(timer) ./C++/bintreetest

	echo "C++/prefixtrie" >> results
	$(timer) ./C++/prefixtrietest $(dict)
	$(timer) ./C++/prefixtrietest $(dict)
	$(timer) ./C++/prefixtrietest $(dict)
	$(timer) ./C++/prefixtrietest $(dict)
	$(timer) ./C++/prefixtrietest $(dict)
	$(timer) ./C++/prefixtrietest $(dict)
	$(timer) ./C++/prefixtrietest $(dict)
	$(timer) ./C++/prefixtrietest $(dict)
	$(timer) ./C++/prefixtrietest $(dict)
	$(timer) ./C++/prefixtrietest $(dict)

	echo "CPython/binarytree" >> results
	$(timer) python2 ./CPython/binarytree/btreetest.py
	$(timer) python2 ./CPython/binarytree/btreetest.py
	$(timer) python2 ./CPython/binarytree/btreetest.py
	$(timer) python2 ./CPython/binarytree/btreetest.py
	$(timer) python2 ./CPython/binarytree/btreetest.py
	$(timer) python2 ./CPython/binarytree/btreetest.py
	$(timer) python2 ./CPython/binarytree/btreetest.py
	$(timer) python2 ./CPython/binarytree/btreetest.py
	$(timer) python2 ./CPython/binarytree/btreetest.py
	$(timer) python2 ./CPython/binarytree/btreetest.py

	echo "Python/binarytree" >> results
	$(timer) pypy ./Python/btree.py
	$(timer) pypy ./Python/btree.py
	$(timer) pypy ./Python/btree.py
	$(timer) pypy ./Python/btree.py
	$(timer) pypy ./Python/btree.py
	$(timer) pypy ./Python/btree.py
	$(timer) pypy ./Python/btree.py
	$(timer) pypy ./Python/btree.py
	$(timer) pypy ./Python/btree.py
	$(timer) pypy ./Python/btree.py

	rm ./C++/bintreetest ./C++/prefixtrietest

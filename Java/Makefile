all:
	cd BinaryTree; make
	cd BubbleSort; make

testbtree:
	/usr/bin/time -f "%e - %M" -a -o ../results	java -cp . BinaryTree.BinaryTree

import std.stdio, std.random;

class Node(T) {
	Node!T left;
	Node!T right;
	T *value;

	void Insert(T val) {
		if (value == null) {
			*(value = new T()) = val;
			left = new Node!T;
			right = new Node!T;
			return;
		}

		if (*value > val) {
			return left.Insert(val);
		}
		return right.Insert(val);
	}

	void Walk() {
		if (value == null)
			return;
		left.Walk();
		writeln(*value);
		right.Walk();
	}
}

int main() {
	Node!int root = new Node!int; 

	foreach(num; 1 .. 1000000) {
		auto i = uniform(0, num);
		root.Insert(i);
	}
	return 0;
}
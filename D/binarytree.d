import std.stdio, std.random;

class Node(T) {
    Node!T left;
    Node!T right;
    T *value;

    void Insert(T val) {
        Node!T n;
        n = this;
        while (n.value) {
            if (*n.value > val)
                n = n.left;
            else
                n = n.right;
        }
        *(n.value = new T()) = val;
        n.left = new Node!T;
        n.right = new Node!T; 
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
    root.Walk();
    return 0;
}
package BinaryTree;


public class Strval implements Comparable<Strval> {
    public String val;

    public Strval(String s) {
	this.val = s;
    }

    @Override public int compareTo(Strval other) {

	if (val.length() == other.val.length()) {
	    return 0;
	}
	if (val.length() < other.val.length()) {
	    return -1;
	}

	return 1;
    }
}

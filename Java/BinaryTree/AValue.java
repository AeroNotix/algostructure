package BinaryTree;

public class AValue implements Comparable<AValue> {
    public int val;

    public AValue(Integer i) {
	this.val = i;
    }

    @Override public int compareTo(AValue other) {

	if (val == other.val) {
	    return 0;
	}

	if (val < other.val) {
	    return -1;
	}
	return 1;
    }
}

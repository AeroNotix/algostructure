/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bubbleSort;

/**
 *
 * @author kratochb
 */
public class SVal implements Comparable<SVal>{
    public String val;

    public SVal(String s) {
	this.val = s;
    }

    @Override public int compareTo(SVal other) {

	if (val.length() == other.val.length()) {
	    return 0;
	}
	if (val.length() < other.val.length()) {
	    return -1;
	}

	return 1;
    }    
}

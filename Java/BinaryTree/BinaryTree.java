package BinaryTree;

import java.util.ArrayList;

public class BinaryTree {

    private Tree root;

    public static void main(String[] args) {
	BinaryTree binTree = new BinaryTree();
	binTree.addLeaf(new AValue(4));
	binTree.addLeaf(new AValue(-5));
	binTree.addLeaf(new AValue(6));
	binTree.addLeaf(new AValue(5));
	binTree.addLeaf(new AValue(7));
	binTree.addLeaf(new AValue(1));
	binTree.addLeaf(new AValue(3));

	for (Comparable c :  binTree.walk()) {
	    AValue v = (AValue) c;
	    System.out.println(v.val);
	}

	BinaryTree binTree2 = new BinaryTree();
	binTree2.addLeaf(new Strval("ABC"));
	binTree2.addLeaf(new Strval("A"));
	binTree2.addLeaf(new Strval("AOIjD"));
	binTree2.addLeaf(new Strval("ASDOIJASD"));
	binTree2.addLeaf(new Strval("ASDOINa"));
	binTree2.addLeaf(new Strval("AB"));
	binTree2.addLeaf(new Strval(""));

	for (Comparable c :  binTree2.walk()) {
	    Strval v = (Strval) c;
	    System.out.println(v.val);
	}
    }

    public BinaryTree(){
	root = null;
    }

    public void addLeaf(Comparable val){
	if (root == null){
	    root = new Tree(val);
	    System.out.println(root.value+" base");
	    return;
	}

	if (val.compareTo(root.value) == 1){
	    if (root.right == null){
		root.right = new Tree(val);
	    } else {
		addLeaf(val, root.right);
	    }
	    return;
	}

	if (root.left == null){
	    root.left = new Tree(val);
	} else {
	    addLeaf(val, root.left);
	}
    }

    public void addLeaf(Comparable val, Tree leaf){
	if (val.compareTo(leaf.value) == 1 ){
	    if (leaf.right == null){
		leaf.right = new Tree(val);
	    } else {
		addLeaf(val, leaf.right);
	    }
	    return;
	}

	if (leaf.left == null){
	    leaf.left = new Tree(val);
	} else {
	    addLeaf(val, leaf.left);
	}
    }

    public ArrayList<Comparable> walk(){
	ArrayList<Comparable> listOf = new ArrayList<>();

	if(root == null){
	    return listOf;
	}

	walk(root.left, listOf);
	walk(root.right, listOf);

	return listOf;
    }

    public ArrayList walk(Tree leaf, ArrayList listOf){
	if (leaf == null){
	    return listOf;
	}

	walk(leaf.left, listOf);
	listOf.add(leaf.value);
	walk(leaf.right, listOf);

	return listOf;
    }
}

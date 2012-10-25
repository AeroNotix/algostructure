package BinaryTree;

import java.util.ArrayList;
import java.util.Random;

public class BinaryTree {

    private Tree root;

    public static void main(String[] args) {
		BinaryTree binTree = new BinaryTree();

		for (int x = 0; x < 1000000; x++) {
			binTree.addLeaf(new AValue(x));
		}
	}

    public BinaryTree() {
		root = null;
    }

    public void addLeaf(Comparable val) {
		if (root == null) {
			root = new Tree(val);
			System.out.println(root.value+" base");
			return;
		}

		if (val.compareTo(root.value) == 1){
			if (root.right == null) {
				root.right = new Tree(val);
			} else {
				addLeaf(val, root.right);
			}
			return;
		}

		if (root.left == null) {
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

		if(root == null) {
			return listOf;
		}

		walk(root.left, listOf);
		walk(root.right, listOf);

		return listOf;
    }

    public ArrayList walk(Tree leaf, ArrayList listOf){
		if (leaf == null) {
			return listOf;
		}

		walk(leaf.left, listOf);
		listOf.add(leaf.value);
		walk(leaf.right, listOf);

		return listOf;
    }
}

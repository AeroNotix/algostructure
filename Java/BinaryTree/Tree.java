package BinaryTree;

public class Tree {
    public Tree left;
    public Tree right;
    public Comparable value;


    public Tree(Comparable val){
        this.value = val;
        this.left = null;
        this.right = null;
    }
}

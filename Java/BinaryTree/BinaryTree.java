package binTree;

import java.util.ArrayList;

public class BinaryTree {

	private Tree root;
	
		public static void main(String[] args) {
			BinaryTree binTree = new BinaryTree();
			binTree.addLeaf(4);
			binTree.addLeaf(-5);
			binTree.addLeaf(6);
			binTree.addLeaf(5);
			binTree.addLeaf(7);
			binTree.addLeaf(1);
			binTree.addLeaf(3);
			binTree.walk();
		}

		public BinaryTree(){
			root = null;
		}

		public void addLeaf(Integer val){
			if (root == null){
				root = new Tree(val);
				System.out.println(root.value+" base");
				return;
			}

			if (val > root.value){
                            if (root.right ==null){
				root.right = new Tree(val);
                                 System.out.println("right Node Added");
                            } else {
                                addLeaf(val, root.right);
                            }    
				return;
			} 

                        if (root.left == null){
                            root.left = new Tree(val);
                            System.out.println("left Node Added");
                        } else {
                            addLeaf(val, root.left);
                        }
		}

		public void addLeaf(Integer val, Tree leaf){
			if (val > leaf.value){
                            if (leaf.right == null){
				leaf.right = new Tree(val);
                                 System.out.println("right Node Added");
                            } else {
                                addLeaf(val, leaf.right);
                               
                            }
				return;
			}
                        
			if (leaf.left == null){
                            leaf.left = new Tree(val);
                            System.out.println("left Node Added");
                            
                        } else {
                            addLeaf(val, leaf.left);
                        }    
		}

		public void walk(){
                    ArrayList<Integer> listOf = new ArrayList<>();
			if(root == null){
				return;
			}

			walk(root.left, listOf);
			walk(root.right, listOf);


			for (Integer i:listOf){
				System.out.println(i);
			}
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
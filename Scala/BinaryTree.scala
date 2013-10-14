// generic immutable binary tree
sealed trait BinaryTree[T] {
  def add(value: T)(implicit ordering: Ordering[T]): BinaryTree[T]
  def walk(f: T => Unit) {}
}

case class Empty[T]() extends BinaryTree[T] {
  override def add(value: T)(implicit ordering: Ordering[T]) = 
    Node[T](value, this, this)
}

case class Node[T](value: T, left: BinaryTree[T], right: BinaryTree[T])
  extends BinaryTree[T] {
  override def add(newValue: T)(implicit ordering: Ordering[T]) =
    if (ordering.gt(newValue, value)) copy(right = right.add(newValue))
    else copy(left = left.add(newValue))

  override def walk(f: T => Unit) {
    left.walk(f)
    f(value)
    right.walk(f)
  }
}

object BinaryTree {
  def create[T]: BinaryTree[T] = Empty[T]
}

var tree = BinaryTree.create[Int]

for (i <- 1 to 1000000) {
  val value = scala.util.Random.nextInt(i)
  tree = tree.add(value)
}

tree.walk(println)

// canonical quicksort example

def quickSort(xs: List[Int]): List[Int] = xs match {
  case Nil          => Nil
  case head :: tail =>
    val (smaller, bigger) = tail.partition(_ < head)
    quickSort(smaller) ::: head :: quickSort(bigger)
}

println(quickSort(List(3, 2, 4, 6, 5, 1, 7, 8)))

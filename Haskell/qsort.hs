quicksort [] = []
quicksort (x:xs) =
  let left = quicksort [y | y <- xs, y <= x]
      right = quicksort [y | y <- xs, y > x]
  in left ++ [x] ++ right
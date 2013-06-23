bsort [] = []
bsort (x:[]) = [x]
bsort (x:x2:xs)
  | x < x2 = x:(bsort (x2:xs))
  | otherwise = x2:(bsort (x:xs))

loop num f x
  | num > 0 = loop (num-1) f x'
  | otherwise = x
  where x' = f x

bubblesort list = loop (length list) bsort list
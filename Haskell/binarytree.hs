data Tree x = EmptyTree | Node x (Tree x) (Tree x)
            deriving (Show)

singleton :: a -> Tree a
singleton a = Node a EmptyTree EmptyTree

insertTree :: (Ord a) => a -> Tree a -> Tree a
insertTree a EmptyTree = singleton a
insertTree x (Node a left right)
  | x == a = (Node x left right)
  | x <  a = (Node a (insertTree x left) right)
  | x >  a = (Node a left (insertTree x right))

elemTree :: (Ord a) => a -> Tree a -> Bool
elemTree x EmptyTree = False
elemTree x (Node a left right)
  | x == a = True
  | x <  a = elemTree x left
  | x >  a = elemTree x right

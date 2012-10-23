(defun quicksort (els)
  (if (= (length els) 0)
	  l
	(append (quicksort 
			 (remove-if-not 
			  #'(lambda (x) (<= x (nth (round (/ (length els) 2)) els))) els))
			(list (nth (round (/ (length els) 2)) els))
			(quicksort
			 (remove-if-not 
			  #'(lambda (x) (> x (nth (round (/ (length els) 2)) els))) els)))))

(print (quicksort '(123 14 41 1 2 )))
(print (quicksort '(1 1 1 1 1 1)))
(print (quicksort '(1 2 3 4 5 6)))
(print (quicksort '(6 5 4 3 2 1)))

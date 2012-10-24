(defun get-random (li)
  (nth (random (length li)) li))

(defun quicksort (li)
  (if (= (length li) 0)
      li
    (let ((mid (get-random li)))
      (append
       (quicksort
	(remove-if-not #'(lambda (x) (< x mid)) li))
       (list mid)
       (quicksort
	(remove-if-not #'(lambda (x) (> x mid)) li))))))

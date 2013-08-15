(defclass Node ()
  ((prefix :accessor pre :initarg :pre :initform nil)
   (nodes :accessor nodes :initarg :nodes :initform '())))

(defun nprefix (s1 s2)
  "nprefix takes two strings and computes the length of the longest
  prefix of each of the strings."
  (mismatch s1 s2))

(defun sprefix (s1 s2)
  "sprefix takes two strings and returns the longest prefix of the
  strings as a string."
  (let ((differ-point (nprefix s1 s2)))
    (if (equal differ-point 0)
	"" ;; if they differ at the beginning then just return ""
      (subseq s1 0 differ-point))))

(defmethod insert ((n Node) (s string))
  (if (equal nil (pre n))
      (add-to-self n s)
    (add-to-subnode n s)))

(defmethod add-to-self ((n Node) (s string))
  (setf (pre n) s))

(defmethod add-to-node ((n Node) (s string))
  :ok)

(defmethod add-to-subnode ((n Node) (s string))
  (let ((loop-index 0))
    (loop for subn in (nodes n)
	  do (let ((common-prefix (sprefix (pre subn) s)))
	       (if (> (length common-prefix) 0)
		   (if (string= (pre subn) s)
		       (progn
			 (print (list s (pre subn)))
			 (add-to-node subn (subseq s (length common-prefix)))
			 (return-from add-to-subnode))
		     (progn
		       (setf (pre subn) (subseq s (length common-prefix)))
		       (setf (nth loop-index (nodes n))
			     (make-instance 'Node :pre common-prefix :nodes (list subn)))
		       (add-to-subnode (nth loop-index (nodes n)) (subseq s (length common-prefix)))
		       (return-from add-to-subnode)))
		 (incf loop-index)))))
  (push (make-instance 'Node :pre s) (nodes n)))

(defun walk-nodes ((n Node))
  (print (pre n))
  (dolist (node (nodes n))
    (walk-nodes node)))

(defvar *root* (make-instance 'Node))
(insert *root* "bread")
(insert *root* "breadpudding")
(walk-nodes *root*)

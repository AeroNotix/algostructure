(defclass Node ()
  ((prefix :accessor pre :initarg :pre :initform nil)
   (nodes :accessor nodes :initarg :nodes :initform '())))

(defun nprefix ((s1 string) (s2 string))
  "nprefix takes two strings and computes the length of the longest
  prefix of each of the strings."
  (let ((use (if (< (length s1) (length s2))
		 s1
	       s2))
	(pre 0))
    (loop for x from 0 below (length use)
	  do (incf pre)
	  while (char= (char s1 x) (char s2 x)))
    pre))

(defun sprefix (s1 s2)
  "sprefix takes two strings and returns the longest prefix of the
  strings as a string."
  (let ((differ-point (nprefix s1 s2)))
    (if (= differ-point 0)
	"" ;; if they differ at the beginning then just return ""
      (substring s1 0 differ-point))))

(defmethod insert ((n Node) (s string))
  (if (equal nil (pre n))
      (add-to-self n s)
    (add-to-subnode n s)))

(defmethod add-to-self ((n Node) (s string))
  (setf (pre n) s))

(defmethod add-to-subnode ((n Node) (s string))
  (let ((found nil))
    (loop for subn in (nodes n)
	  while (null found)
	  do (let ((common-prefix (sprefix (pre subn) s)))
	       (if (string= (pre subn) s)
		   (add-to-node subn (substring s (length common-prefix)))
		 (progn))
	       (setq found t)))
  (push (make-instance 'Node :pre s) (nodes n))))
	       

(defvar *root* (make-instance 'Node))
(insert *root* "something")
(print (pre *root*))
(insert *root* "somethingelse")
(insert *root* "somethingelse2")
(print (nodes *root*))

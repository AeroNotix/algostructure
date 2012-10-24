(defclass Node ()
  ((value :initarg :value :initform nil :accessor v)
   (left :initarg :left :initform nil :accessor l)
   (right :initarg :right :initform nil :accessor r)))

(defmethod insert ((n Node) (i number))
  (if (not (v n))
      (progn
	(setf (v n) i)
	(setf (l n) (make-instance 'Node))
	(setf (r n) (make-instance 'Node)))
    (if (> (v n) i)
	(insert (l n) i)
      (insert (r n) i))))

(defmethod value ((n Node))
  (v n))

(defmethod walk ((n Node))
  (if (not (v n))
      nil
    (progn
      (walk (l n))
      (print (v n))
      (walk (r n)))))

(setq root (make-instance 'Node))

(insert root 1)
(insert root 123)
(insert root 413)
(insert root 13)
(insert root 66)
(insert root 2)
(print (v root))

(walk root)

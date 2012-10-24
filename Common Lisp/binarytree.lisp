(defclass Node ()
  ((value :initarg :value :initform nil :accessor v)
   (left :initarg :left :initform nil :accessor l)
   (right :initarg :right :initform nil :accessor r)))

(defmethod insert ((n Node) (i number))
  (if (not (value n))
      (progn
	(setf (v n) i)
	(setf (l n) (make-instance 'Node))
	(setf (r n) (make-instance 'Node)))
    (if (> (value n) i)
	(insert (l n) i)
      (insert (r n) i))))

(defmethod value ((n Node))
  (v n))

(defmethod walk ((n Node))
  (if (not (value n))
      nil
    (progn
      (walk (l n))
      (print (value n))
      (walk (r n)))))

(defmethod addrandom ((n Node) (i number))
  (if (= i 0)
      nil
    (progn
      (insert n (random i))
      (addrandom n (- i 1)))))

(defun main()
  (setq root (make-instance 'Node))
  (addrandom root 1000000)
  (exit))

(main)

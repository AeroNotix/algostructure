(defclass Node ()
  ((prefix :accessor pre :initarg pre :initform nil)
   (nodes :accessor subn :initarg nodes :initform '())))

(defmethod insert ((n Node) (s string))
  (if (not (pre n))
      (setf (pre n) s)))
    

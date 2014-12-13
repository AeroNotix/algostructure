;; ##############################################
;; #           Cardinality Estimation           #
;; Papers:
;; http://www.cse.unsw.edu.au/~cs9314/07s1/lectures/Lin_CS9314_References/fm85.pdf [Flajolet - Martin]
;; http://www.ic.unicamp.br/~celio/peer2peer/math/bitmap-algorithms/durand03loglog.pdf [Durand - Flajolet]
;; http://algo.inria.fr/flajolet/Publications/FlFuGaMe07.pdf [Flajolet et al.]
;; Inspired from: http://blog.notdot.net/2012/09/Dam-Cool-Algorithms-Cardinality-Estimation
  
;; estimate-cardinality: (listof HashTables) Nat -> Nat
;; Purpose: Produces an estimation of the number of unique elements in the input set values.
(define (estimate-cardinality values bucket-exponent)

;; Helpers:
(define (max-zeroes bucket-index hash lst_val)
  (append (max (max-zeroes bucket-index hash lst_val

(define (shift-bucket-hash hash bucket-exponent)
  (airthmetic-shift hash bucket-exponent))
  
;; trailing-zeroes: Num -> (union 32 Nat)
;; Purpose: Counts the number of trailing 0 bits in num.
(define (trailing_zeroes num)
  (cond [(equal? num 0)
          32 ; Assume 32-bit integer inputs]
        [else
          (count-trailing num)]))
          
;; count-trailing: Num -> Nat
;; Logical helper for trailing-zeroes
(define (count-trailing num acc)
  (cond [(equal? (bitwise-and (arithmetic-shift num acc) 1) 0)
          (count-trailing num (+ acc 1))]
        [else acc]))
    

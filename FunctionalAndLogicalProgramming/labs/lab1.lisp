; Ф-ция вычисляет количество атомов в списочной стpуктуpе на всех уровнях
(defun atom_cnt (l &optional (cnt 0))
  (cond
    ((null l) cnt)
    ((atom (car l)) (atom_cnt (cdr l) (+ cnt 1)))
    (t (+ (atom_cnt (car l)) (atom_cnt (cdr l) cnt)))
  )
)

(print "(a s (3 4) 1 2)")
(print "atoms count: ")
(princ (atom_cnt '(a s (3 4) 1 2)))

(print "((1 (2 3 4 (((5)) (6)) 7) 8) 9 10)")
(print "atoms count: ")
(princ (atom_cnt '((1 (2 3 4 (((5)) (6)) 7) 8) 9 10)))

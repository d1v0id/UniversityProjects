; Ф-ция оставляет только один элемент в списке из каждой группы подряд идущих элементов.
(defun only_one (l)
  (cond
    ((null l) nil)
    ((null (cdr l)) l)
    ((equal (car l) (cadr l)) (only_one (cdr l)))
    (t (cons (car l) (only_one (cdr l))))
  )
)

(print "(1 1 1 2 3 3 4 4 4 4)")
(print "after only_one: ")
(princ (only_one '(1 1 1 2 3 3 4 4 4 4)))
;;(load "nd.ss")
(import (draga nondeterminism))

;; Choose 2 example  (see _On Lisp_, sec, 22.1 (pp. 286-289)
(define (choose-2)
  (reset-nd!)
  (let ([x (choose '(1 2))])
    (if (odd? x) (fail) x)))

;; Parlor Trick example (see _On Lisp_, sec, 22.2 (pp. 290-292)
(define (two-numbers)
  (list (choose '(0 1 2 3 4 5))
        (choose '(0 1 2 3 4 5))))

(define (parlor-trick sum)
  (reset-nd!)
  (let ((nums (two-numbers)))
    (if (= (apply + nums) sum)
        `(the sum of ,@nums)
        (fail))))

;; Chocoblob Coin Search example (with cuts) (see _On Lisp_, sec, 22.5 (pp. 298-302)
(define (find-boxes)
  (reset-nd!)
  (let ([city (choose '(la ny bos))])
    (mark)
    (newline)
    (let* ([store (choose '(1 2))]
           [box (choose '(1 2))])
      (let ([triple (list city store box)])
        (display triple)
        (when (coin? triple)
          (cut)
          (display 'c))
        (fail)))))

(define (coin? x)
  (member x '((la 1 2) (ny 1 1) (bos 2 2))))

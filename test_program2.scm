(define (koch-line length depth)
   (if (zero? depth)
	 (tortoise-move length)
	 (let ((sub-length (/ length 3))
		   (sub-depth (1- depth)))
	   (for-each (lambda (angle)
				   (koch-line sub-length sub-depth)
				   (tortoise-turn angle))
				 '(60 -120 60 0)))))
 
 (define (snowflake length depth sign)
   (let iterate ((i 1))
	 (if (<= i 3)
	   (begin
		 (koch-line length depth)
		 (tortoise-turn (* sign -120))
		 (iterate (1+ i))))))
 
 (snowflake 8 3 1)
 (tortoise-turn 180)
 (snowflake 8 3 -1)

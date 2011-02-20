; test lists

()	; easy Nil

  ( 	; trickier,
)	; but still Nil

(() . ())	; simple dotted pair; should yield “( () )”

(	; explicit construction of list; should yield “( ( () ) )”
 (() . ())
 .
 ()
)

(	; another explicit construction; should yield “( () () )”
 ()
 .
 (() . ())
)

# My very own implementation of Scheme

This is **`jcscheme`**, my very own implementation of the language.
My intention is to learn Scheme by implementing it.

As may be evident from the “forked from” line on GitHub,
this effort was inspired by Peter Michaux’s Bootstrap Scheme,
described in his [blog][pmss]
and available at [petermichaux/bootstrap-scheme][pmbs].

Other inspirations are:

* Abdulaziz Ghuloum’s [*An Incremental Approach to Compiler Construction*][agcc]
  and his [compilers tutorial][agct],
* Paul Wilson’s [*An Introduction to Scheme and its Implementation*][isai],
* Léon Bottou’s [MiniLisp][mini], and
* Various [S-expression][wiki] libraries,
  particularly Ronald Rivest’s [SEXP][sexp]
  and [sfsexp][sfsexp] from LANL’s supermon project.

As in Bootstrap Scheme, the structure of the interpreter is based on
[*Structure and Interpretation of Computer Programs*][sicp].
All code, however, is my own.

[agcc]: http://scheme2006.cs.uchicago.edu/11-ghuloum.pdf
[agct]: http://www.cs.indiana.edu/~aghuloum/
[isai]: ftp://ftp.cs.utexas.edu/pub/garbage/cs345/schintro-v14/schintro_toc.html
[pmss]: http://peter.michaux.ca/articles/scheme-from-scratch-introduction
[pmbs]: http://github.com/petermichaux/bootstrap-scheme
[mini]: http://leon.bottou.org/projects/minilisp
[wiki]: http://en.wikipedia.org/wiki/S-expression
[sexp]: http://people.csail.mit.edu/rivest/sexp.html
[sfsexp]: http://sexpr.sourceforge.net/
[sicp]: http://mitpress.mit.edu/sicp/

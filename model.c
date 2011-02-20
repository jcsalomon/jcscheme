#include "jcscheme.h"

// Nil
static const expr nil[] = {
	{.tag = T_NIL},
};
expr const * const Nil = nil;

extern inline bool is_nil(expr const *exp);


// Lists
expr const*
cons(expr const *car, expr const *cdr)
{
	expr *list = emalloc(sizeof *list);
	*list = (expr) {
		.tag = T_PAIR,
		{ (struct cons) {.car = car, .cdr = cdr} }
	};
	return list;
}

#undef car
#undef cdr
extern inline bool is_pair(expr const *exp);
extern inline expr const* car(expr const *list);
extern inline expr const* cdr(expr const *list);


// Symbols
expr const*
make_symbol(char const *str)
{
	expr *symbol = emalloc(sizeof *symbol);
	*symbol = (expr) {.tag = T_SYMBOL, {.symb = str}};
	return symbol;
}

extern inline bool is_symbol(expr const *exp);

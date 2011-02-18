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


// Symbols & symbol table
static expr symbol_table[];

static expr const* make_new_symbol(char const *str);

expr const*
make_symbol(char const *str)
{
	expr const *node = symbol_table;
	for (;;) {
		int cmp = strcmp(str, node->car->symb);
		if (cmp == 0)
			return node->car;

		expr *branches = (expr *)node->cdr;
		/* search left branch if cmp < 0, otherwise right branch
		 * if branch is empty, create symbol, and the node to contain it,
		 *   attach node to appropriate branch in tree, & return new symbol
		 * otherwise follow branch (recursion turned into loop)
		 *
		 * see _Symbol Table Layout Explained_ in the wiki
		 */
		if (cmp < 0) {
			if (branches->car == Nil) {
				expr const *sym = make_new_symbol(str);
				branches->car = cons(sym, cons(Nil, Nil));
				return sym;
			}
			else {
				node = branches->car;
				continue;
			}
		}
		else if (cmp > 0) {
			if (branches->cdr == Nil) {
				expr const *sym = make_new_symbol(str);
				branches->cdr = cons(sym, cons(Nil, Nil));
				return sym;
			}
			else {
				node = branches->cdr;
				continue;
			}
		}
	}
}

expr const*
make_new_symbol(char const *str)
{
	expr *symbol = emalloc(sizeof *symbol);
	*symbol = (expr) {.tag = T_SYMBOL, {.symb = str}};
	return symbol;
}

extern inline bool is_symbol(expr const *exp);

static expr symbol_table[3] = {
	[0] = {.tag = T_PAIR, {{.car = symbol_table+1, .cdr = symbol_table+2}}},
	[1] = {.tag = T_SYMBOL, {.symb = "[]"}},
	[2] = {.tag = T_PAIR, {{.car = nil, .cdr = nil}}}
};
expr * const Symbol_Table = symbol_table;

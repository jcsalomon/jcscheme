#ifndef JCSCHEME_TREE_H_
#define JCSCHEME_TREE_H_


#define DEFINE_SYMTAB_NODE(node, str, left, right) \
	static expr node[3] = { \
		[0] = {.tag = T_PAIR, {{.car = node+1, .cdr = node+2}}},            \
		[1] = {.tag = T_SYMBOL, {.symb = str}},                             \
		[2] = {.tag = T_PAIR, {{.car = left##_node, .cdr = right##_node}}}, \
	}

#define Nil_node nil

#define DEFINE_SYMBOL(name, sym, left, right) \
	DEFINE_SYMTAB_NODE(sym##_node, #sym, left, right)

#define NAME_SYMBOL(name, sym, left, right) \
	expr const * const name = sym##_node+1

// dummy symbol “[]” for root of tree; 'Z' < '[' < 'a'
#define DEFINE_SYMTAB(name, sym, left, right) \
	DEFINE_SYMTAB_NODE(sym, "[]", left, right)

// attach name to root of tree, not the dummy symbol
#define NAME_SYMTAB(name, sym, left, right) \
	expr * const name = sym


#endif

#include "jcscheme.h"

static void print_list(expr const *list);

void
print(expr const *exp)
{
	switch (exp->tag) {
		case T_NIL:
			printf("()");
			break;
		case T_PAIR:
			printf("(");
			print_list(exp);
			printf(")");
			break;
		default:
			fatal("unknown type %x", exp->tag);
	}
}

void
print_list(expr const *list)
{
	print(list->car);
	printf(" . ");
	print(list->cdr);
}

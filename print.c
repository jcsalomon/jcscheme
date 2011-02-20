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
		case T_SYMBOL:
			printf("%s", exp->symb);
			break;
		default:
			fatal("unknown type %x", exp->tag);
	}
}

void
print_list(expr const *list)
{
	print(list->car);

	switch (list->cdr->tag) {
		case T_NIL:  // “(~ . ())” = “(~)”; print nothing
			break;
		case T_PAIR: // “(~ . (…))” = “(~ …)”; no parentheses around list->cdr
			printf(" ");
			print_list(list->cdr);
			break;
		default:
			printf(" . ");
			print(list->cdr);
			break;
	}
}

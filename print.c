#include "jcscheme.h"

void
print(expr const *exp)
{
	switch (exp->tag) {
		case T_NIL:
			printf("()");
			break;
		default:
			fatal("unknown type %x", exp->tag);
	}
}

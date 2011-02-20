#include "jcscheme.h"

// Nil
static const expr nil[] = {
	{.tag = T_NIL},
};
expr const * const Nil = nil;

extern inline bool is_nil(expr const *exp);

#include "jcscheme.h"

static inline bool is_self_evaluating(expr const* exp)
	__attribute__((nonnull));

static inline bool is_tagged_list(expr const *exp, expr const *tag)
	__attribute__((nonnull));

static inline bool is_quoted(expr const *exp)
	__attribute__((nonnull));


expr const*
eval(expr const *exp)
{
	if (is_self_evaluating(exp)) {
		return exp;
	}
	else if (is_quoted(exp)) {
		// 'pick-me = (quote pick-me) = (quote . (pick-me . () ) )
		return exp->cdr->car;
	}
	else {
		fprintf(stderr, "%s\n", "not self-evaluating");
		return Nil;
	}
}

bool
is_self_evaluating(expr const *exp)
{
	return is_symbol(exp);
}

bool
is_tagged_list(expr const *exp, expr const *tag)
{
	return is_pair(exp)
		&& is_symbol(exp->car)
		&& is_pair(exp->cdr)
		&& exp->car == tag;
}

bool is_quoted(expr const *exp)
{
	return is_tagged_list(exp, Quote);
}

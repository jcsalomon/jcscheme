#include "jcscheme.h"

static int get_next_nonspace(FILE *in);
static inline int peek(FILE *in);

inline static bool is_symbol_char(int c);

static expr const* read_list(FILE *in);
static expr const* read_list_cdr(FILE *in);
static expr const* read_symbol(FILE *in);


expr const*
read(FILE *in)
{
	int c = get_next_nonspace(in);

	if (c == EOF) {
		return NULL;
	}
	else if (c == '(') {
		return read_list(in);
	}
	else if (is_symbol_char(c)) {
		ungetc(c, in);
		return read_symbol(in);
	}
	else if (c == '\'') {
		return cons(Quote, cons(read(in), Nil));
	}
	else {
		fatal("unrecognized input");
	}
	unreached();
}

expr const*
read_list(FILE *in)
{
	// initial ‘(’ already consumed
	int c = get_next_nonspace(in);

	if (c == ')') {
		return Nil;
	}

	ungetc(c, in);

	expr const * const car = read(in);
	if (car == NULL) {
		fatal("incomplete list");
	}

	expr const * const cdr = read_list_cdr(in);
	if (cdr == NULL) {
		fatal("incomplete list");
	}

	return cons(car, cdr);
}

expr const*
read_list_cdr(FILE *in)
{
	int c = get_next_nonspace(in);

	if (c == '.') {
		expr const * const cdr = read(in);

		if ((c = get_next_nonspace(in)) != ')') {
			fatal("unclosed list");
		}
		return cdr;
	}
	else {
		ungetc(c, in);

		return read_list(in);
	}
}

expr const*
read_symbol(FILE *in)
{
	size_t i = 0, n = 64;
	char *buf = emalloc(n);

	int c;
	while ((c = getc(in)), is_symbol_char(c))
	{
		buf[i++] = (char)c;

		// if we’re at buffer’s end & there’s more to come, grow buffer
		if (i == n-1 && is_symbol_char(peek(in)) )
			buf = erealloc(buf, n *= 2);
	}
	assert (i < n); // sanity check
	buf[i] = '\0';
	
	ungetc(c, in);
	return make_symbol(buf);
}

int
get_next_nonspace(FILE *in)
{
	int c;
	while ((c = getc(in)) != EOF) {
		if (isspace(c)) {
			continue;
		}
		if (c == ';') {
			while ((c = getc(in)), c != EOF && c != '\n')
				;
			continue;
		}
		break;
	}
	return c;
}

int
peek (FILE *in)
{
	int c = getc(in);
	ungetc(c, in);
	return c;
}

bool
is_symbol_char(int c)
{
	return isalpha(c) || isdigit(c)
		|| c == '+' || c == '-' || c == '*' || c == '/'
		|| c == '<' || c == '>' || c == '='
		|| c == '~' || c == '!' || c == '@' || c == '#'
		|| c == '$' || c == '%' || c == '^' || c == '&'
		|| c == '|' || c == '"' || c == '.' || c == '?';
}

#include "jcscheme.h"

static int get_next_nonspace(FILE *in);
static inline int peek(FILE *in);


expr const*
read(FILE *in)
{
	int c = get_next_nonspace(in);

	if (c == EOF) {
		return NULL;
	}
	else {
		fatal("unrecognized input");
	}
	unreached();
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
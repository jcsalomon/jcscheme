#include "jcscheme.h"

static void
jcscheme(FILE *in)
{
	while (1) {
		if (in == stdin) {
			printf("> ");
			fflush(stdout);
		}

		expr const *exp = read(in);
		if (exp == NULL)
			return;

		print(eval(exp));
		printf("\n");
	}
}

int
main(int argc, char *argv[argc+1])
{
	argv0 = "jcscheme";

	if (argc == 1)
		jcscheme(stdin);
	else for (int i = 1; i < argc; i++) {
			FILE *f = fopen(argv[i], "r");
			if (f == NULL)
				fatal("cannot open %s", argv[i]);
			jcscheme(f);
			fclose(f);
		}
	if (0) print(Symbol_Table); // enable for debugging
	exit(EXIT_SUCCESS);
}

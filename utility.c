#include "jcscheme.h"

#undef trace
#undef fatal
#undef emalloc
#undef erealloc

char const *argv0;

static void
verror(struct location loc, char const *fmt, va_list argp)
{
	int e = errno;
	char errbuf[64];

	fprintf(stderr, "%s: %s(): ", argv0, loc.func);
	vfprintf(stderr, fmt, argp);
	if (e) {
		int s = strerror_r(e, errbuf, nelem(errbuf));
		if (s == 0)
			fprintf(stderr, ": %s", errbuf);
	}
	fprintf(stderr, "\n");
}

void
trace(struct location loc, char const *fmt, ...)
{
	va_list argp;
	va_start(argp, fmt);
	verror(loc, fmt, argp);
	va_end(argp);
}


#define fatal(loc, ...) do { \
		trace(loc, __VA_ARGS__); \
		exit(EXIT_FAILURE); \
	} while (0)

void*
emalloc(struct location loc, size_t size)
{
	void *p = malloc(size);
	if (p == NULL)
		fatal(loc, "malloc");
	return p;
}

void*
erealloc(struct location loc, void *ptr, size_t size)
{
	if (size == 0) {
		free(ptr);
		return NULL;
	}
	void *p = realloc(ptr, size);
	if (p == NULL)
		fatal(loc, "realloc");
	return p;
}


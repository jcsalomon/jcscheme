#ifndef JCSCHEME_H_
#define JCSCHEME_H_


#include <stdarg.h>

#include <ctype.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Model
typedef struct cell {
} expr;


// Read
extern expr const* read(FILE *in);


// Evaluate
inline expr const* eval(expr const *exp) __attribute__((nonnull));
inline expr const* eval(expr const *exp) {return exp;}


// Print
extern void print(expr const *exp) __attribute__((nonnull));


// Utilities
extern char const *argv0;

#define nelem(a) ( (sizeof (a) / sizeof (a)[0])	   \
                   / !(sizeof (a) % sizeof (a)[0]) \
                   / !(sizeof (a) < sizeof (a)[0]) )

struct location {
	char const *func;
	char const *file;
	int line;
};

extern void trace(struct location loc, char const *fmt, ...)
	__attribute__((format(printf, 2, 3)));
#define trace(...) \
	trace((struct location){__func__, __FILE__, __LINE__}, __VA_ARGS__)

#define fatal(...) do { \
		trace(__VA_ARGS__); \
		exit(EXIT_FAILURE); \
	} while (0)

extern void* emalloc(struct location loc, size_t size)
	__attribute__((malloc));
#define emalloc(size) \
	emalloc((struct location){__func__, __FILE__, __LINE__}, size)

#define unreached() do { \
		fatal("reached the unreachable"); \
	} while (0)


#endif

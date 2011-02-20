#ifndef JCSCHEME_H_
#define JCSCHEME_H_


#include <stdarg.h>
#include <stdbool.h>

#include <ctype.h>

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Model
typedef struct cell {
	enum {
		T_NIL,
		T_PAIR,
	} tag;
	union {
		struct cons {
			struct cell const *car;
			struct cell const *cdr;
		};
	};
} expr;

// nil, the empty list
extern expr const * const Nil;

inline bool is_nil(expr const *exp) __attribute__((nonnull));
inline bool is_nil(expr const *exp) {return exp == Nil;}

// lists
extern expr const* cons(expr const *car, expr const *cdr)
	__attribute__((malloc));

inline bool is_pair(expr const *exp) __attribute__((nonnull));
inline bool is_pair(expr const *exp) {return exp->tag == T_PAIR;}

inline expr const* car(expr const *pair) __attribute__((nonnull));
inline expr const* car(expr const *pair) {return pair->car;}

inline expr const* cdr(expr const *pair) __attribute__((nonnull));
inline expr const* cdr(expr const *pair) {return pair->cdr;}

/* assertions are in macros rather than the inline functions
 * for better diagnostics on constructions like “car(expression->member)”
 */
#define car(pair) (assert (is_pair(pair)), car(pair))
#define cdr(pair) (assert (is_pair(pair)), cdr(pair))


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

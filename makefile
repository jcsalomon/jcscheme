CC = gcc

CSTD  = -std=gnu99
CEXTS = -fms-extensions
CWARN = -Wall -Wextra -Wno-missing-field-initializers -Winline \
	 -Wmissing-prototypes -Wconversion -Wlogical-op
CFLAGS = $(CSTD) $(CEXTS) $(CWARN)

CPPINCL =
CPPDEFS =
CPPFLAGS = $(CPPINCL) $(CPPDEFS)

LDDIRS =
LDLIBS =
LDFLAGS = $(LDDIRS) $(LDLIBS)

JCSCHEME = jcscheme

DEPS = jcscheme.h
OBJS = jcscheme.o utility.o read.o eval.o print.o

TESTS = whitespace

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

$(JCSCHEME): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS)

.PHONY: clean test

clean:
	-rm -f $(JCSCHEME) $(OBJS) *.out

test: $(JCSCHEME)
	for t in $(TESTS); do \
	    $(JCSCHEME) test/$$t.ss > $$t.out 2>&1; \
	    diff $$t.out test/$$t.cmp > /dev/null || \
		echo Test $$t failed >&2; \
	done

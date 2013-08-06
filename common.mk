# Utilities
GCC      ?= gcc
LEX      ?= flex
YACC     ?= bison
CT       ?= ct

CFLAGS   ?= -Wall -Werror -g --std=c99

ifdef PKGS
CPPFLAGS += $(shell pkg-config --cflags $(PKGS))
LDFLAGS  += $(shell pkg-config --libs   $(PKGS))
endif

# Targets
all: $(PROG)

clean:
	rm -f $(PROG) *.o *.a parse.h parse.c scan.c

# C Rules
$(PROG): $(SOURCES:%.c=%.o)
	$(GCC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

%.o: %.c makefile
	$(GCC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

# Lex / Yacc rules
%.c: %.l parse.h makefile
	$(LEX) -o $@ $<

%.c %.h: %.y makefile
	$(YACC) -d -o $*.c $*.y

# CT Rules
%.c: %.ct makefile
	$(CT) -o $@ $<

# Miscellaneous
.SECONDARY:

# vim: ft=make

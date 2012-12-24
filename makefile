# Settings
PROG     = ct
CC       = gcc
YACC     = bison
LEX      = flex

CFLAGS   = -Wall -Werror -g --std=c99
CPPFLAGS = $(shell pkg-config --cflags glib-2.0)
LDFLAGS  = $(shell pkg-config --libs   glib-2.0)

# Targets
default: test

all: $(PROG)

test: $(PROG)
	./$(PROG) example/html.ct

clean:
	rm -f $(PROG) *.o *.a parse.h parse.c scan.c

# Rules
$(PROG): ct.o parse.o scan.o
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

%.o: %.c parse.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

%.c: %.l parse.h
	$(LEX) -o $@ $<

%.c %.h: %.y
	$(YACC) -d -o $*.c $*.y

.SECONDARY:

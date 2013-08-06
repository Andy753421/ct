# Settings
CT        = ../ct
PROG      = knot
SOURCES   = knot.c html.c
CPPFLAGS  = -I..

# Targets
test: crown.html hitch.html overhand.html

# Rules
%.html: %.txt knot makefile
	./knot < $< > $@

include ../common.mk

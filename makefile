# Settings
PROG     = ct
SOURCES  = ct.o parse.o scan.o
PKGS     = glib-2.0

test: $(PROG)
	./$(PROG) example/html.ct

include common.mk

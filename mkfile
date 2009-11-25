PROGS=ct lib
PKGS=glib-2.0
default:V: run
lib-run:V: lib
	./lib
ct-run:V: ct
	./ct < example/html.ct
ct: ct.o parse.o scan.o
ct.o: parse.h
parse.h parse.c: parse.y
	bison -d -o parse.c parse.y
scan.c: scan.l parse.h
	flex -o scan.c scan.l
CLEAN=parse.h parse.c scan.c
<$HOME/lib/mkcommon

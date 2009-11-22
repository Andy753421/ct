PROGS=ct
PKGS=glib-2.0
ct-test:V: ct
	./ct < example/html.ct
ct: ct.o scan.o parse.o parse.h
%.c: %.l
	flex -o $target $prereq
%.h %.c: %.y
	bison -d -o $stem.c $stem.y
CLEAN=parse.h parse.c scan.c
<$HOME/lib/mkcommon

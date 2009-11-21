PKGS=glib-2.0
PROGS=test
default:V: test
	#cat test.c
	./test
test: test.o lib.o
lib.c: lib.ct tmpl.awk
	./tmpl.awk <lib.ct >lib.c
	ex +'norm gg=G' +'wq' lib.c
<$HOME/lib/mkcommon

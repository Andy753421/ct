# Settings
CT        = ../ct
PROG      = gallery
SOURCES   = gallery.c html.c ../lib.c
CPPFLAGS  = -I..
PKGS      = glib-2.0

# Targets
test: gallery
	QUERY_STRING=foo ./gallery

# Rules
../lib.o: CFLAGS += -Wno-format

include ../common.mk

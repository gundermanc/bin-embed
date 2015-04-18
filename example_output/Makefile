#
# Binary File Header Generator Example
# (C) 2015 Christian Gunderman
#
CFLAGS=-Wall --std=c99 --pedantic
OUTFILE=example-output
LNFLAGS=

# Debug flags
DFLAGS=-g -DDEBUG

# Release flags
RFLAGS=

# Targets to build
SOURCES=main.c

.PHONY: all
all: CFLAGS+=$(RFLAGS)
all: link

.PHONY: all-debug
all-debug: CFLAGS+=$(DFLAGS)
all-debug: link

.PHONY: clean
clean:
	$(RM) *~
	$(RM) *.o
	$(RM) $(OUTFILE)
	$(RM) image_data.h
	$(RM) image_after.jpg

link:
	../bin-embed kImageData image_before.jpg image_data.h
	$(CC) $(CFLAGS) $(SOURCES) -o $(OUTFILE) $(LNFLAGS)

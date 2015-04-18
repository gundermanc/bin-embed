#
# Binary File Header Generator
# (C) 2015 Christian Gunderman
#
CFLAGS=-Wall --std=c99 --pedantic
OUTFILE=bin-embed
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

link:
	$(CC) $(CFLAGS) $(SOURCES) -o $(OUTFILE) $(LNFLAGS)

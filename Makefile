TOP=.
SRCDIR =$(TOP)/src
BINDIR =$(TOP)/bin
INCLUDE = -I$(TOP)/include -I$(SRCDIR)
SRC=$(wildcard $(SRCDIR)/*.c)

.PHONY: all
all: calc

calc:  $(SRC)
	gcc -g $(INCLUDE) $(SRC)  -o $(BINDIR)/calc

.PHONY: test

test:
	$(BINDIR)/calc dump lex "(+ 1 2)"


.PHONY: clean

clean:
	rm $(BINDIR)/calc > /dev/null  2>&1


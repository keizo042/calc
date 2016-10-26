TOP=.
SRCDIR =$(TOP)/src
BINDIR =$(TOP)/bin
INCLUDE = -I$(TOP)/include -I$(SRCDIR) -lm
SRC=$(wildcard $(SRCDIR)/*.c)

.PHONY: all
all: calc

calc:  $(SRC)
	[ -d $(TOP)/bin ] || mkdir $(TOP)/bin
	gcc -g $(INCLUDE) $(SRC)  -o $(BINDIR)/calc

.PHONY: test

test:
	$(BINDIR)/calc "(+ 1 2)"
	$(BINDIR)/calc "(- 1 2)"
	$(BINDIR)/calc "(* 1 2)"
	$(BINDIR)/calc "(/ 1 2)"
	$(BINDIR)/calc "(+ (+1 2) 2)"
	$(BINDIR)/calc "(+ (- 2 1) 0)"


.PHONY: clean

clean:
	rm -rf $(BINDIR) > /dev/null  2>&1

.PHONY: lex

lextest:
	$(BINDIR)/calc dump lex "(+ 1 2)"
	$(BINDIR)/calc dump lex "(+ 100 200)"

.PHONY: parse

parsetest: 
	$(BINDIR)/calc dump parse "(+ 1 2)"

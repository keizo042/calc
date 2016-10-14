SRCDIR =./src
BINDIR =./bin
INCLUDE = -I ./include
SRC=$(wildcard $(SRCDIR)/*.c)

.PHONY: all
all: calc

calc:  $(SRC)
	gcc -g $(INCLUDE) $(SRC)  -o $(BINDIR)/calc

.PHONY: clean

clean:
	rm $(BINDIR)/calc > /dev/null  2>&1


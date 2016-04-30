SRCDIR =./src
BINDIR =./bin
INCLUDE = -I ./include
SRC=$(wildcard $(SRCDIR)/*.c)

.PHONY: all
all: calc

calc:  $(SRC)
	gcc $(INCLUDE) $(SRC)  -o $(BINDIR)/calc

.PHONY: clean

clean:
	rm $(SRCDIR)/*.o $(BINDIR)/kcc


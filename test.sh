#!/bin/sh
BINDIR=./bin
$BINDIR/calc "(+ 1 2)"
$BINDIR/calc "(- 1 2)"
$BINDIR/calc "(* 1 2)"
$BINDIR/calc "(* 4 2)"
$BINDIR/calc "(/ 1 2)"
$BINDIR/calc "(+ (+1 2) 2)"
$BINDIR/calc "(+ (- 2 1) 0)"
$BINDIR/calc "(+ (/ 2 1) 10)"
$BINDIR/calc "(/ 1 0)"

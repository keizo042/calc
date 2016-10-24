#ifndef CALC_H
#define CALC_H
#include "lex.h"
#include "parser.h"
#include "ast.h"
lex_state *lex(char *src);
parser_stack_t *lex_token_stream2parser_stack(lex_token_stream *);
#endif

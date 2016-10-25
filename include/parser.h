#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "lex.h"


struct parser_state;
typedef struct parser_state_s parser_state;


struct parser_stack_s;
typedef struct parser_stack_s parser_stack_t;

struct parser_stack_s {
    parser_stack_t *prev;
    expr *expr;
};


struct parser_state_s {
    lex_token_stream *stream;
    parser_stack_t *stack;
    expr *result;
    int err;
};


int parser_state_lex_token_stream_next(parser_state *);
expr *parser_expr(parser_state *);
parser_stack_t *expr2stack(expr *);
parser_state *parse(lex_state *);

#endif

#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "lex.h"

struct parser_state;
typedef struct parser_state_s parser_state;

typedef int (*statefn_t)(parser_state *);

struct parser_stack_s;
typedef struct parser_stack_s parser_stack_t;

struct parser_stack_s {
    parser_stack_t *prev;
    ast_t *ast;
};


struct parser_state_s {
    lex_token_stream *stream;
    parser_stack_t *stack;
    statefn_t fn;
    int err;
};


parser_state *parse(lex_state *);
ast_t *parser_ast(parser_state *);

#endif

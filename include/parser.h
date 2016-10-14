#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "lex.h"

typedef int (*statefn_t)();

struct parser_stack_s {
    int tag;
    ast_t *ast;
};
typedef struct parser_state_s parser_stack_t;

struct parser_state_s {
    parser_stack_t *stack;
    statefn_t state;
    int err;
};
typedef struct parser_state_s parser_state;

parser_state *parse(lex_state *);
ast_t *parser_ast(parser_state *);

#endif

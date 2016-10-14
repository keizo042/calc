#include <stdio.h>
#include <stdlib.h>

#include "ast.h"
#include "lex.h"
#include "parser.h"

static parser_state *parser_state_open();

#define PARSER_END 0
#define PARSER_CONTINUE 1

parser_stack_t *parser_stack_pop(parser_state *state) {
    parser_stack_t *stack;
    stack        = state->stack;
    state->stack = stack->prev;
    stack->prev  = NULL;
    return stack;
}

int parser_stack_push(parser_state *state, parser_stack_t *elem) {
    elem->prev   = state->stack;
    state->stack = elem->prev;
    return 0;
}

static int parse_init(parser_state *state);

static int parse_init(parser_state *state) { return PARSER_END; }

static parser_state *parser_state_open() {
    parser_state *state = malloc(sizeof(parser_state));
    state->fn           = parse_init;
    state->err          = 0;
    return state;
}

parser_state *parse(lex_state *lexer) {
    parser_state *state = parser_state_open();
    state->stream       = lexer->head;
    int ret             = PARSER_CONTINUE;

    while (ret == PARSER_CONTINUE) {
        ret = state->fn(state);
        break;
    }
    return state;
}

ast_t *parser_ast(parser_state *parser) { return NULL; }

#include <stdio.h>
#include <stdlib.h>

#include "ast.h"
#include "calc.h"
#include "lex.h"
#include "parser.h"

static parser_state *parser_state_open();
expr *lex_token_stream2expr(lex_token_stream *data) ;

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
static int parse_binop(parser_state *state);
static int parse_end(parser_state *state);

static int parse_init(parser_state *state) {
    switch (state->stream->data->tag) {
    case TOK_PLUS:
    case TOK_MIN:
    case TOK_MUITI:
    case TOK_DIV:
        return parse_binop(state);
    case TOK_PAREN_L:
        return parse_binop(state);
    case TOK_PAREN_R:
        return parse_end(state);
    case TOK_DIGIT:
        parser_stack_push(state, expr2stack(lex_token_stream2expr(state->stream)));
        return PARSER_END;
    }
}

static int parse_binop(parser_state *state) { return PARSER_END; }

static int parse_end(parser_state *state){
    return PARSER_END;
}

static parser_state *parser_state_open() {
    parser_state *state = malloc(sizeof(parser_state));
    state->fn           = parse_init;
    state->err          = 0;
    state->result       = NULL;
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

expr *lex_token_stream2expr(lex_token_stream *data) {
    return NULL;
}
parser_stack_t *expr2stack(expr *expr){
    return NULL;
}

expr *parser_expr(parser_state *parser) { return parser->result; }

#include <stdio.h>
#include <stdlib.h>

#include "ast.h"
#include "calc.h"
#include "lex.h"
#include "parser.h"

static parser_state *parser_state_open();
expr *lex_token2expr(lex_token *);

#define PARSER_END 0
#define PARSER_CONTINUE 1

parser_stack_t *parser_stack_pop(parser_state *state) {
    parser_stack_t *stack;
    stack        = state->stack;
    state->stack = stack->prev;
    stack->prev  = NULL;
    return stack;
}

int parser_stack_push(parser_state *state, expr *expr) {
    parser_stack_t *stack = malloc(sizeof(parser_stack_t));
    stack->expr           = expr;

    stack->prev  = state->stack;
    state->stack = stack->prev;
    return 0;
}


int parser_state_lex_token_stream_next(parser_state *state) {
    state->stream = state->stream->next;
    return 0;
}

static int parse_init(parser_state *state);
static int parse_binop(parser_state *state);
static int parse_end(parser_state *state);

static int parse_init(parser_state *state) {
    switch (state->stream->data->tag) {
    case TOK_EOL:
        return PARSER_END;
    case TOK_PLUS:
    case TOK_MIN:
    case TOK_MUITI:
    case TOK_DIV:
        return PARSER_CONTINUE;
    case TOK_PAREN_L:
        return parse_init(state);
    case TOK_PAREN_R:
        return parse_end(state);
    case TOK_DIGIT:
        parser_stack_push(state, NULL);
        return PARSER_CONTINUE;
    }
}

static int parse_binop(parser_state *state) {
    parser_stack_t *stack = NULL;
    expr *e1 = NULL, *e2 = NULL, *e3 = NULL, *eresult = NULL;
        parser_stack_push(state, lex_token2expr(state->stream->data));

        parser_state_lex_token_stream_next(state);
        parse_init(state);
        stack = parser_stack_pop(state);
        e1    = stack->expr;

        parser_state_lex_token_stream_next(state);
        parse_init(state);
        stack = parser_stack_pop(state);
        e2    = stack->expr;
        parser_stack_pop(state);
        e3                     = stack->expr;
        eresult                = malloc(sizeof(expr));
        eresult->tag              = AST_BINOP;
        eresult->data.binop->binop = e3->data.op;
        eresult->data.binop->lval  = e2;
        eresult->data.binop->rval  = e3;
        parser_stack_push(state, eresult);
}

static int parse_end(parser_state *state) { return PARSER_CONTINUE; }

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

expr *lex_token2expr(lex_token *data) { return NULL; }
parser_stack_t *expr2stack(expr *expr) { return NULL; }

expr *parser_expr(parser_state *parser) { return parser->result; }

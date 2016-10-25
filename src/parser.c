#include <stdio.h>
#include <stdlib.h>

#include "ast.h"
#include "calc.h"
#include "lex.h"
#include "parser.h"

static parser_state *parser_state_open();

#define PARSER_END 0
#define PARSER_CONTINUE 1

parser_stack_t *parser_stack_pop(parser_state *state) {
    parser_stack_t *stack;
    if (state->stack == NULL) {
        return NULL;
    }
    stack = state->stack;
    if (stack->prev != NULL) {
        state->stack = stack->prev;
        stack->prev  = NULL;
    } else {
        state->stack = NULL;
    }

    return stack;
}

int parser_stack_push(parser_state *state, expr *expr) {
    parser_stack_t *stack = malloc(sizeof(parser_stack_t));
    stack->expr           = expr;

    stack->prev  = state->stack;
    state->stack = stack;
    return 0;
}


int parser_state_lex_token_stream_next(parser_state *state) {
    state->stream = state->stream->next;
    return 0;
}

int parser_state_lex_token_tag(parser_state *state) { return state->stream->data->tag; }



static int parse_init(parser_state *state);
static int parse_binop(parser_state *state);
static int parse_end(parser_state *state);
static int parse_digit(parser_state *state);

static int parse_init(parser_state *state) {
    expr *e1 = NULL, *e2 = NULL;
    parser_stack_t *stack;
    switch (parser_state_lex_token_tag(state)) {
    case TOK_EOL:
        return PARSER_END;
    case TOK_PLUS:
    case TOK_MIN:
    case TOK_MUITI:
    case TOK_DIV:
        return parse_binop(state);
    case TOK_PAREN_L:
        e1 = malloc(sizeof(expr));
        parser_state_lex_token_stream_next(state);
        parse_init(state);
        stack      = parser_stack_pop(state);
        e2         = stack->expr;
        e1->tag    = AST_EXPR;
        e1->data.e = e2;
        parser_stack_push(state, e1);
        return PARSER_CONTINUE;
    case TOK_PAREN_R:
        return parse_end(state);
    case TOK_DIGIT:
        return parse_digit(state);
    }
}

static int parse_binop(parser_state *state) {
    parser_stack_t *stack = NULL;
    expr *e1 = NULL, *e2 = NULL, *eresult = NULL, *t = NULL;

    eresult                = malloc(sizeof(expr));
    eresult->tag           = AST_BINOP;
    eresult->data.binop.op = *state->stream->data->tok;

    parser_state_lex_token_stream_next(state);
    parse_init(state);
    stack = parser_stack_pop(state);
    e1    = stack->expr;

    parser_state_lex_token_stream_next(state);
    parse_init(state);
    stack = parser_stack_pop(state);
    e2    = stack->expr;

    eresult->data.binop.lval = e1;
    eresult->data.binop.rval = e2;
    parser_stack_push(state, eresult);
    return PARSER_CONTINUE;
}

static int parse_digit(parser_state *state) {
    expr *e       = malloc(sizeof(expr));
    e->tag        = AST_DIGIT;
    e->data.digit = atoi(state->stream->data->tok);
    parser_stack_push(state, e);
    return PARSER_CONTINUE;
}
static int parse_end(parser_state *state) {
    parser_state_lex_token_stream_next(state);
    return PARSER_CONTINUE;
}

static parser_state *parser_state_open() {
    parser_state *state = malloc(sizeof(parser_state));
    state->err          = 0;
    state->result       = NULL;
    return state;
}

parser_state *parse(lex_state *lexer) {
    parser_state *state = parser_state_open();
    state->stream       = lexer->head;
    parser_stack_t *stack      = NULL;
    int ret             = PARSER_CONTINUE;

    while (ret == PARSER_CONTINUE) {
        ret = parse_init(state);
        break;
    }
    stack = parser_stack_pop(state);
    state->result =stack->expr;
    return state;
}

parser_stack_t *expr2stack(expr *expr) { return NULL; }

expr *parser_expr(parser_state *parser) { return parser->result; }

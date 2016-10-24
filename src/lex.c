#include "lex.h"
#include "calc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_P(i) ('0' <= (i) && (i) <= '9')

#define CONTINUE 1
#define END 0



static lex_token *lex_token_new(char *, int, int);
static lex_token_stream *lex_token_stream_open();
static lex_state *lex_state_open(char *);
static int lex_text(lex_state *);
static int lex_ident(lex_state *);
static int lex_emit(lex_state *, int);


static lex_token *lex_token_new(char *tok, int len, int tag) {
    lex_token *token = malloc(sizeof(lex_token));
    token->tok       = malloc(sizeof(char) * (len + 1));
    strncpy(token->tok, tok, len);
    token->tag = tag;
    return token;
}


static lex_token_stream *lex_token_stream_open() {
    lex_token_stream *stream = malloc(sizeof(lex_token_stream));
    stream->data             = NULL;
    stream->next             = NULL;

    return stream;
}


static lex_state *lex_state_open(char *src) {
    lex_state *state = malloc(sizeof(lex_state));
    state->src       = src;
    state->start     = state->src;
    state->pos       = 0;
    state->len       = 0;
    state->head      = lex_token_stream_open();
    state->tail      = state->head;

    state->err = 0;
    return state;
}

void lex_token_stream_p(lex_token_stream *stream) {
    printf("lex_token_stream:");
    for (lex_token_stream *head = stream; head == NULL; head = head->next) {
        printf("{%s,%d},", head->data->tok, head->data->tag);
    }
    printf("\t");
    return;
}

void lex_state_p(lex_state *state) {
    printf("state->start:%s\t", state->start);
    printf("state->pos:%d\t", state->pos);
    printf("state->len:%d\t", state->len);
    lex_token_stream_p(state->head);
    printf("state->err:%d\t", state->err);
    return;
}


static char lex_state_next(lex_state *state) {
    return *(state->start + state->pos + state->len + 1);
}
static char lex_state_peek(lex_state *state) { return *(state->start + state->pos); }
static char lex_state_pook(lex_state *state) {
    return *(state->start + state->pos + state->len - 1);
}

static char lex_state_incr(lex_state *state) {
    state->len++;
    state->pos++;
    return *(state->start + state->pos + state->len);
}

static char lex_state_decr(lex_state *state) {
    if (state->len > 0) {
        state->len--;
        state->pos--;
    }
    return *(state->start + state->pos + state->len);
}

static int lex_emit(lex_state *state, int typ) {
    lex_token *token         = lex_token_new(state->start, state->len, typ);
    lex_token_stream *stream = lex_token_stream_open();

    state->tail->data = token;

    state->tail->next = stream;
    state->tail       = stream;

    state->start = state->start + state->pos;
    state->len   = 0;
    state->pos   = 0;

    return CONTINUE;
}

lex_token_stream *lex_state_stream(lex_state *state) { return state->head; }
lex_token_stream *lex_token_stream_next(lex_token_stream *stream) { return stream->next; }


int lex_text(lex_state *state) {
    while (1) {
        switch (lex_state_peek(state)) {
        case '\0':
            return END;
        case ' ':
        case '\n':
        case '\t':
            state->pos++;
            return CONTINUE;
        case '(':
            lex_state_incr(state);
            return lex_emit(state, TOK_PAREN_L);
        case ')':
            lex_state_incr(state);
            return lex_emit(state, TOK_PAREN_R);
        case '*':
            lex_state_incr(state);
            return lex_emit(state, TOK_MUITI);
        case '-':
            lex_state_incr(state);
            return lex_emit(state, TOK_MIN);
        case '+':
            lex_state_incr(state);
            return lex_emit(state, TOK_PLUS);
        case '/':
            lex_state_incr(state);
            return lex_emit(state, TOK_DIV);
        default:
            return lex_ident(state);
        }
    }
}

int lex_ident(lex_state *state) {
    while (NUM_P(lex_state_peek(state))) {
        lex_state_incr(state);
    }
    state->len++;
    return lex_emit(state, TOK_DIGIT);
}

lex_state *lex(char *src) {
    lex_state *state = lex_state_open(src);
    int ret          = CONTINUE;
    while (ret == CONTINUE) {
        ret = lex_text(state);
    }
    if (state->err) {
        return NULL;
    } else {
        return state;
    }
}

const char *lex_token_typ_str(lex_token *token) {
    switch (token->tag) {
    case TOK_PAREN_L:
        return "TOK_PAREN_L";
    case TOK_PAREN_R:
        return "TOK_PAREN_R";
    case TOK_MUITI:
        return "TOK_MUITI";
    case TOK_MIN:
        return "TOK_MIN";
    case TOK_PLUS:
        return "TOK_PLUS";
    case TOK_DIV:
        return "TOK_DIV";
    case TOK_DIGIT:
        return "TOK_DIGIT";
    default:
        return "undefined";
    }
}

const char *lex_token_sym_str(lex_token *token) { return token->tok; }

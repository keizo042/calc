#ifndef LEX_H
#define LEX_H

#define TOK_DIGIT 1
#define TOK_PLUS 2
#define TOK_MIN 3
#define TOK_MUITI 4
#define TOK_DIV 5
#define TOK_PAREN_L 6
#define TOK_PAREN_R 7


struct lex_token {
    int tag;
    char *tok;
};
typedef struct lex_token lex_token;

struct lex_token_stream {
    lex_token *data;
    struct lex_token_stream *next;
};
typedef struct lex_token_stream lex_token_stream;

struct lex_state {
    char *src;
    char *start;
    int pos;
    int len;
    lex_token_stream *head;
    lex_token_stream *tail;

    int err;
};
typedef struct lex_state lex_state;

lex_token_stream *lex_state_stream(lex_state *);
const char *lex_token_typ_str(lex_token *);
const char *lex_token_sym_str(lex_token *);
#endif

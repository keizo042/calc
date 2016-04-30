#include <stdio.h>

#define TOK_DIGIT
#define TOK_PLUS
#define TOK_MIN
#define TOK_MUITI
#define TOK_DIV
#define TOK_PAREN_L
#define TOK_PAREN_R

typedef struct lex_token {
    int tag;
    char *tok;
}lex_token;

typedef struct lex_token_stream {
    lex_token *data;
    lex_token_stream *next;
}lex_token_stream;

typedef struct lex_state {
    lex_token_stream *head;
    lex_token_stream *now;
}lex_state;

lex_state* lex(FILE *fp)
{
}

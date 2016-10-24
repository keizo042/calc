#include "calc.h"
#include "ast.h"
#include "interp.h"
#include "lex.h"
#include "parser.h"
#include <stdio.h>
#include <string.h>

int lex_token_stream_pp(lex_state *state);
int parser_ast_pp(parser_state *state);

void help() {
    char *desc[] = {"", NULL};

    for (int i = 0; desc[i] != NULL; i++) {
        printf("%s\n", desc[i]);
    }
}


int main(int argc, char *argv[]) {
    lex_state *lexer     = NULL;
    parser_state *parser = NULL;
    expr *expr           = NULL;

    if (argc < 2) {
        help();
        return 0;
    }
    if (strncmp("dump", argv[1], 4) == 0) {
        if (argc < 4) {
            help();
            return 0;
        }
        lexer = lex(argv[2]);
        if (lexer == NULL) {
            printf("lexer fail\n");
            return -1;
        }
        lex_token_stream_pp(lexer);
        parser = parse(lexer);
        if (parser->err == 1) {
            printf("parse fail\n");
            return -1;
        }
        parser_ast_pp(parser);
        return 0;
    }
    lexer = lex(argv[1]);
    if (lexer == NULL) {
        printf("lexer fail\n");
        return -1;
    }
    parser = parse(lexer);
    if (parser->err == 1) {
        printf("parse fail\n");
        return -1;
    }
    expr = parser_expr(parser);
    printf("%d\n", run(expr));

    return 0;
}

int lex_token_stream_pp(lex_state *state) {

    printf("{");
    for (lex_token_stream *stream = state->head; stream->data != NULL; stream = stream->next) {
        printf("%s:%s,", lex_token_typ_str(stream->data), lex_token_sym_str(stream->data));
    }
    printf("}\n");
    return 0;
}

int parser_ast_pp(parser_state *state) { return 0; }

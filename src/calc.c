#include "calc.h"
#include "ast.h"
#include "interp.h"
#include "lex.h"
#include "parser.h"
#include <stdio.h>
#include <string.h>

int lex_token_stream_pp(lex_state *state);
int parser_ast_pp(parser_state *state);
int dump(int, char **);

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
        dump(argc - 1, argv + 1);
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

int expr_pp(expr *expr);
int binop_pp(binop_t *binop);

int binop_pp(binop_t *binop) {
    printf("%c ", binop->op);
    expr_pp(binop->lval);
    expr_pp(binop->rval);
    return 0;
}

int expr_pp(expr *expr) {
    printf("(");
    switch (expr->tag) {
    case AST_DIGIT:
        printf("%d", expr->data.digit);
    case AST_BINOP:
        binop_pp(&(expr->data.binop));
    }
    printf(")");
}


int parser_ast_pp(parser_state *state) {
    expr *expr = parser_expr(state);
    if (expr == NULL)
        return -1;
    expr_pp(expr);
    return 0;
}

int dump(int argc, char **argv) {
    char *src            = NULL;
    lex_state *lexer     = NULL;
    parser_state *parser = NULL;
    if (argc < 2) {
        help();
        return 0;
    }
    if (argc == 3) {
        if (strncmp("lex", argv[1], 3) == 0) {
            src   = argv[2];
            lexer = lex(src);
            lex_token_stream_pp(lexer);
            return 0;
        }
        if (strncmp("parse", argv[1], 5) == 0) {
            src    = argv[2];
            lexer  = lex(src);
            parser = parse(lexer);
            parser_ast_pp(parser);
            return 0;
        }
        return -1;
    } else {
        src = argv[1];
    }

    lexer = lex(src);
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

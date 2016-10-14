#include "ast.h"
#include "lex.h"
#include "parser.h"
#include "interp.h"
#include <stdio.h>
#include <string.h>

void help() {
    char **desc = {NULL};

    for (int i = 0; strcmp(desc[i], "") != 0; i++) {
        printf("%s\n", desc[i]);
    }
}


int main(int argc, char *argv[]) {
    lex_state *lexer     = NULL;
    parser_state *parser = NULL;
    ast_t *ast = NULL;

    if (argc < 2) {
        help();
        return 0;
    }
    lexer = lex(argv[1]);
    if (lexer == NULL) {
        printf("lexer fail\n");
        return -1;
    }
    parser = parse(lexer);
    if (parser == NULL) {
        return -1;
    }
    if(parser->err = 1)
    {
        return -1;
    }
    ast = parser_ast(parser);
    run(ast);

    return 0;
}

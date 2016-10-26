#include "ast.h"
#include <stdlib.h>

int run(expr *expr)
{
    switch (expr->tag)
    {

        case AST_BINOP:
            return -2;
            
        case AST_DIGIT:
            return expr->data.digit;
        case AST_EXPR:
            return run(expr->data.e);
        default:
            return -1;
    }
    return 0;
}

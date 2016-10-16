#include "ast.h"
#include <stdlib.h>

int run(expr *expr)
{
    switch (expr->tag)
    {

        case AST_BINOP:
            return -2;
            
        case AST_DIGIT:
            return atoi( expr->data.sym);
        default:
            return -1;
    }
    return 0;
}

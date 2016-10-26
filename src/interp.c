#include "ast.h"
#include <math.h>
#include <stdlib.h>

int run(expr *expr)
{
            int res = 0,
                r = 0,
                l = 0;
    switch (expr->tag)
    {

        case AST_BINOP:
            l = run(expr->data.binop.lval);
            r = run(expr->data.binop.rval);
            switch(expr->data.binop.op)
            {
                case '+':
                    return (l + r);
                case '-':
                    return (l - r);
                case '/':
                    if(r == 0)
                    {
                        return 0;
                    }else{
                        return (l / r);
                    }

                case '*':
                    return (l * r);
            }
            
        case AST_DIGIT:
            return expr->data.digit;
        case AST_EXPR:
            return run(expr->data.e);
        default:
            return -1;
    }
    return 0;
}

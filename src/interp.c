#include "ast.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int run(expr *expr) {
    int res = 0, r = 0, l = 0;
    if (expr == NULL) {
        puts("null expr");
        exit(-1);
    }
    switch (expr->tag) {

    case AST_BINOP:
        l = run(expr->data.binop.lval);
        r = run(expr->data.binop.rval);
        switch (expr->data.binop.op) {
        case '+':
            return (l + r);
        case '-':
            return (l - r);
        case '/':
            if (r == 0) {
                printf("can not divide zero\n");
                exit(-1);
            } else {
                return (l / r);
            }

        case '*':
            return (l * r);
        default:
            printf("calc can only accept + - / *\n");
            exit(-1);
        }

    case AST_DIGIT:
        return expr->data.digit;
    case AST_EXPR:
        if(expr->data.e == NULL)
        {
            exit(-1);
        }
        return run(expr->data.e);
    default:
        return -1;
    }
    return 0;
}

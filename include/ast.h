#ifndef AST_H
#define AST_H

struct binop;
typedef struct binop binop_t;
struct expr;
typedef struct expr expr;

typedef struct ast_s {
    expr *expr;
}ast_t;


#define AST_DIGIT 1
#define AST_BINOP 2

struct expr {
    int tag;
    union {
        char *sym;
        binop_t *binop;
    }data;
};

struct binop {
    char binop;
    expr *lval;
    expr *rval;
};

#endif // AST_H

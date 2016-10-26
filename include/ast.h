#ifndef AST_H
#define AST_H


struct binop;
typedef struct binop binop_t;
struct expr;
typedef struct expr expr;



#define AST_UNDEFINED (-1)
#define AST_DIGIT 1
#define AST_BINOP 2
#define AST_EXPR 3

struct binop {
    char op;
    expr *lval;
    expr *rval;
};

struct expr {
    int tag;
    union {
        int digit;
        binop_t binop;
        expr *e;
    } data;
};


#endif // AST_H

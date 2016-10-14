#include <stdio.h>
#include <stdlib.h>
#include "lex.h"
#include "parser.h"
#include "ast.h"

parser_state* parser_state_open();

#define PARSER_END 0
#define PARSER_CONTINUE 1

static int parse_init(parser_state *state); 

static int parse_init(parser_state *state)
{
    return PARSER_END;
}

parser_state* parser_state_open() 
{
        parser_state* state= malloc( sizeof(parser_state) );
        state->fn = parse_init;
        return NULL;
}

parser_state* parse(lex_state *lexer)
{
    parser_state *state = parser_state_open();
    state->stream = lex_state_stream(lexer);
    int ret = PARSER_CONTINUE;

    while(ret == PARSER_CONTINUE)
    {
        ret = state->fn(state);
        break;
    }
    return state;
}

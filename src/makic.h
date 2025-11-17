#include "builder.h"

typedef enum {
    // basic math
    OP_MUL, OP_DIV,
    OP_ADD, OP_SUB,
    
    // comparison
    OP_EQ, OP_NE, OP_LE,
    OP_GE, OP_LT, OP_GT,
    OP_NOT, OP_IF, OP_IFNOT,
    OP_AND, OP_OR, OP_BITAND, OP_BITOR,

    // compiler
    OP_LOAD, OP_ADDRESS, OP_STORE, OP_STOREP,
    OP_CALL, OP_GOTO, OP_STATE, OP_DONE,
} token_e;
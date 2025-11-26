#include "builder.h"
#include <stdbool.h>

#define MAX_STRINGS     1048576
#define MAX_GLOBALS		524288
#define MAX_FIELDS		2048
#define MAX_STATEMENTS	524288
#define MAX_FUNCTIONS	8192

#define MAX_SOUNDS		2048
#define MAX_MODELS		2048
#define MAX_FILES		2048
#define MAX_DATA_PATH	64
#define MAX_ERRORS		10
#define MAX_NAME		64

#define MAX_REGS		262144

// type of data in makic
typedef enum {
    mc_error = -1,
    mc_void = 0,
    mc_string,
    mc_int,
    mc_bool,
    mc_float,
    mc_entity,
    mc_field,
    mc_function,
    mc_pointer,
} mctype_e;

// type of character
typedef enum {
    CHAR_EOF,
    CHAR_LETTER,
    CHAR_NUMBER,
    CHAR_SQUOTE,
    CHAR_DQUOTE,
    CHAR_DOLLARSIGN,
    CHAR_SPECIAL,
} char_e;

// type of token
typedef enum {
    tt_eof, // end of file
    tt_name, // is an alphanumeric name token
    tt_punct, // code punctuation
    tt_immediate, // immediate / type of value like string, float, vector
} token_type_e;

typedef enum {
    // basic math
    OP_MUL, OP_DIV,
    OP_ADD, OP_SUB,
    
    // comparison
    OP_EQ, OP_NE, OP_LE,
    OP_GE, OP_LT, OP_GT,
    OP_IF, OP_IFNOT, OP_NOT,
    OP_AND, OP_OR, OP_BITAND, OP_BITOR,

    // storage
    OP_STORE, OP_STOREP,

    // compiler
    OP_LOAD, OP_ADDRESS,
    OP_CALL, OP_GOTO, OP_STATE, OP_DONE,
    OP_RETURN,
} opcode_e;

typedef int gofs_t;

typedef struct type_s{
    mctype_e type;
    struct def_s *def;
    struct type_s *next;
    struct type_s *aux_type;
    int num_parms;
    struct type_s *parm_types[MAX_PARMS];
} type_t;

typedef struct def_s {
    type_t *type;
    const char *name;
    struct def_s *next;
    gofs_t ofs;
    struct def_s *scope;
    int initialized;
} def_t;

// opcodes
typedef struct opcode_s {
    const char *name;
    const char *opname;
    int priority;
    bool right_associative;
    def_t *type_a, *type_b, *type_c;
} opcode_t;
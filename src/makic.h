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

// struct types
typedef struct type_s{
    mctype_e type; // int, char, etc
    struct def_s *def;
    struct type_s *next;
    struct type_s *aux_type; // return type or field type
    int num_parms; // -1 = variable args
    struct type_s *parm_types[MAX_PARMS]
} type_t;

// define a variable
typedef struct def_s {
    type_t *type;
    const char *name;
    struct def_s *next;
    gofs_t ofs;
    struct def_s *scope; // function
} def_t;
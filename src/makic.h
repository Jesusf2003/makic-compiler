#include "builder.h"
#include <stdbool.h>

#define MAX_STRINGS 	 1048576
#define MAX_GLOBALS	 524288
#define MAX_FIELDS	 2048
#define MAX_STATEMENTS	 524288
#define MAX_FUNCTIONS	 8192

#define MAX_SOUNDS	 2048
#define MAX_MODELS	 2048
#define MAX_FILES	 2048
#define MAX_DATA_PATH	 64
#define MAX_ERRORS	 10
#define MAX_NAME	 64

#define OFS_NULL 	 0
#define OFS_PARM 	 1
#define OFS_RETURN 	 2
#define RESERVED_OFS 	 3

#define MAX_REGS	 262144
#define MAX_PARMS  	 8

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

// type of token
typedef enum {
    tt_eof, // end of file
    tt_name, // is an alphanumeric name token
    tt_punct, // code punctuation
    tt_immediate, // immediate / type of value like string, float, vector
} token_type_e;

typedef enum {
    str_global,
    str_local,
    str_param,
    str_value, // no asignable
    str_return, // no asignable
} store_type_e;

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

// Define a type in makic
typedef struct mc_type_s
{
    mctype_e type;
    struct def_s *def;
    struct mc_type_s *next;
    struct mc_type_s *aux_type;
    int num_parms;
    struct mc_type_s *parm_types[MAX_PARMS]; 
} mc_type_t;

typedef struct mc_def_s
{
    mc_type_t *type;
    const char *name;
    struct mc_def_s *next;
    gofs_t ofs;
    struct mc_def_s *scope;
    int initialized, ref_count;
    struct mc_def_t *parentVector;
} mc_def_t;
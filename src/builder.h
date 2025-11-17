#include <stdint.h>

typedef enum {
    ev_error = -1,
    ev_void = 0,
    ev_string,
    ev_float,
    ev_vector,
    ev_entity,
    ev_field,
    ev_function,
    ev_pointer,
} evtype_e;

// structure for builder file(progs.src)
typedef struct {
    unsigned int offset;
    unsigned int length;
} builder_section_t;

typedef struct {
    uint32_t version;
    uint16_t crc16;
    uint16_t skip;

    // declaratives in a builder(progs.src) file
    builder_section_t statements;
    builder_section_t defs;
    builder_section_t fields;
    builder_section_t functions;
    builder_section_t strings;
    builder_section_t globals;

    uint32_t entfield; // counter for entity fields
} builder_t;
#include <stdint.h>

#define MAX_PARMS 8

// structure for builder file(progs.src)
typedef struct {
    unsigned int offset;
    unsigned int length;
} builder_section_t;

typedef struct {
    unsigned int version;
    unsigned int crc;

    // declaratives in a builder(progs.src) file
    builder_section_t statements;
    builder_section_t defs;
    builder_section_t fields;
    builder_section_t functions;
    builder_section_t strings;
    builder_section_t globals;

    unsigned int entfield; // counter for entity fields
} builder_t;
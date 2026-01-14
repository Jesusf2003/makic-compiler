#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define MAKIC_DEFINE_FLAGS
#define MAKIC_TYPE_FLAGS

//
#if 1
/* Helpers to allow for a whole lot of flags. Otherwise we'd limit
 * to 32 or 64 -f options...
 */
typedef struct
{
    size_t idx;  /* index into an array of 32 bit words */
    uint8_t bit; /* bit index for the 8 bit group idx points to */
} LongBit;
#define LONGBIT(bit) {((bit) / 32), ((bit) % 32)}
#define LONGBIT_SET(B, I) ((B).idx = (I) / 32, (B).bit = ((I) % 32))
#else
typedef uint32_t longbit;
#define LONGBIT(bit) (bit)
#define LONGBIT_SET(B, I) ((B) = (I))
#endif

enum
{
    #define MAKIC_TYPE_FLAGS
    #define MAKIC_DEFINE_FLAG(X) X,
    #include "opts.def"
    COUNT_FLAGS
};
enum
{
    #define MAKIC_TYPE_WARNS
    #define MAKIC_DEFINE_FLAG(X) WARN_##X,
    #include "opts.def"
    COUNT_WARNINGS
};
enum
{
    #define MAKIC_TYPE_OPTIMIZATIONS
    #define MAKIC_DEFINE_FLAG(NAME, MIN_O) OPTIM_##NAME,
    #include "opts.def"
    COUNT_OPTIMIZATIONS
};
enum
{
    #define MAKIC_TYPE_OPTIONS
    #define MAKIC_DEFINE_FLAG(X) OPTION_##X,
    #include "opts.def"
    OPTION_COUNT
};

// opts
typedef struct {
    union
    {
        bool b;
        uint16_t u16;
        uint32_t u32;
        union
        {
            char *p;
            const char *c;
        } str;
    } data;
    bool allocated;
} opt_value_t;

typedef struct
{
    opt_value_t options[OPTION_COUNT];
    uint32_t flags[1 + (COUNT_FLAGS / 32)];
    uint32_t warn[1 + (COUNT_WARNINGS / 32)];
    uint32_t werror[1 + (COUNT_WARNINGS / 32)];
    uint32_t warn_backup[1 + (COUNT_WARNINGS / 32)];
    uint32_t werror_backup[1 + (COUNT_WARNINGS / 32)];
    uint32_t optimization[1 + (COUNT_OPTIMIZATIONS / 32)];
    bool optimizeoff; /* True when -O0 */
} opts_cmd_t;
extern opts_cmd_t opts;

typedef struct
{
    const char *name;
    LongBit bit;
} opts_flag_def_t;
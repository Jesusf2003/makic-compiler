#ifndef MAKIC_H
#define MAKIC_H

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#define MAKIC_DEFINE_FLAGS
#define MAKIC_TYPE_FLAGS

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
typedef uint32_t LongBit;
#define LONGBIT(bit) (bit)
#define LONGBIT_SET(B, I) ((B) = (I))
#endif

typedef struct
{
    const char *name;
    LongBit bit;
} opts_flag_def_t;

bool opts_setflag(const char *, bool);
bool opts_setwarn(const char *, bool);
bool opts_setwerror(const char *, bool);
bool opts_setoptim(const char *, bool);

void opts_init(const char *, int, size_t);
void opts_set(uint32_t *, size_t, bool);
void opts_setoptimlevel(unsigned int);
void opts_ini_init(const char *);

/* Saner flag handling */
void opts_backup_non_Wall(void);
void opts_restore_non_Wall(void);
void opts_backup_non_Werror_all(void);
void opts_restore_non_Werror_all(void);

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
extern const opts_flag_def_t opts_flag_list[COUNT_FLAGS+1];
extern const opts_flag_def_t opts_warn_list[COUNT_WARNINGS+1];
extern const opts_flag_def_t opts_opt_list[COUNT_OPTIMIZATIONS+1];
extern const unsigned int opts_opt_oflag[COUNT_OPTIMIZATIONS+1];
extern unsigned int opts_optimizationcount[COUNT_OPTIMIZATIONS];

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

#define OPTS_GENERIC(f, i) (!!(((f)[(i) / 32]) & (1U << (unsigned)((i) % 32))))

#define OPTS_FLAG(i) OPTS_GENERIC(opts.flags, (i))
#define OPTS_WARN(i) OPTS_GENERIC(opts.warn, (i))
#define OPTS_WERROR(i) OPTS_GENERIC(opts.werror, (i))
#define OPTS_OPTIMIZATION(i) OPTS_GENERIC(opts.optimization, (i))

#define OPTS_OPTION_DUPED(X) (opts.options[X].allocated)
#define OPTS_OPTION_BOOL(X) (opts.options[X].data.b)
#define OPTS_OPTION_U16(X) (opts.options[X].data.u16)
#define OPTS_OPTION_U32(X) (opts.options[X].data.u32)
#define OPTS_OPTION_STR(X) (opts.options[X].data.str.c)
#define OPTS_OPTION_DUP(X) *(OPTS_OPTION_DUPED(X) = true, &(opts.options[X].data.str.p))

#endif
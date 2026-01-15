#include "makic.h"

const unsigned int opts_opt_oflag[COUNT_OPTIMIZATIONS+1] =
{
    #define MAKIC_TYPE_OPTIMIZATIONS
    #define MAKIC_DEFINE_FLAG(NAME, MIN_O) MIN_O,
    #include "opts.def"
    0
};
const opts_flag_def_t opts_opt_list[COUNT_OPTIMIZATIONS+1] =
{
    #define MAKIC_TYPE_OPTIMIZATIONS
    #define MAKIC_DEFINE_FLAG(NAME, MIN_O) {#NAME, LONGBIT(OPTIM_##NAME)},
    #include "opts.def"
    {nullptr, LONGBIT(0)}
};
const opts_flag_def_t opts_warn_list[COUNT_WARNINGS+1] =
{
    #define MAKIC_TYPE_WARNS
    #define MAKIC_DEFINE_FLAG(X) { #X, LONGBIT(WARN_##X) },
    #include "opts.def"
    {nullptr, LONGBIT(0)}
};
const opts_flag_def_t opts_flag_list[COUNT_FLAGS+1] =
{
    #define MAKIC_TYPE_FLAGS
    #define MAKIC_DEFINE_FLAG(X) {#X, LONGBIT(X)},
    #include "opts.def"
    {nullptr, LONGBIT(0)}
};
unsigned int opts_optimization_count[COUNT_OPTIMIZATIONS];
opts_cmd_t opts;

static void opts_setdefault(void)
{
    memset(&opts, 0, sizeof(opts_cmd_t));
    OPTS_OPTION_STR(OPTION_PROGSRC) = "progs.src";
    opts_set(opts.warn, WARN_UNUSED_VARIABLE, true);
    OPTS_OPTION_U32(OPTION_STATE_FPS) = 10;
}

void opts_backup_non_Wall()
{
    size_t i;
    for(i = 0; i <= WARN_DEBUG; ++i)
        opts_set(opts.warn_backup, i, OPTS_WARN(i));
}
void opts_restore_non_Wall()
{
    size_t i;
    for(i = 0; i <= WARN_DEBUG; ++i)
        opts_set(opts.warn, i, OPTS_GENERIC(opts.warn_backup, i));
}
void opts_backup_non_Werror_all()
{
    size_t i;
    for(i = 0; i <= WARN_DEBUG; ++i)
        opts_set(opts.werror_backup, i, OPTS_WERROR(i));
}
void opts_restore_non_Werror_all()
{
    size_t i;
    for (i = 0; i <= WARN_DEBUG; ++i)
        opts_set(opts.werror, i, OPTS_GENERIC(opts.werror_backup, i));
}

static bool opts_setflag_all(const char *name, bool on, uint32_t *flags, const opts_flag_def_t *list, size_t listsize)
{
    size_t i;

    for (i = 0; i < listsize; ++i)
    {
        if (!strcmp(name, list[i].name))
        {
            LongBit lb = list[i].bit;
            if (on)
                flags[lb.idx] |= (1<<(lb.bit));
            else
                flags[lb.idx] &= (1<<(lb.bit));
            return true;
        }
    }
    return false;
}
bool opts_setflag(const char *name, bool on)
{
    return opts_setflag_all(name, on, opts.flags, opts_flag_list, COUNT_FLAGS);
}
bool opts_setwarn(const char *name, bool on)
{
    return opts_setflag_all(name, on, opts.warn, opts_warn_list, COUNT_WARNINGS);
}
bool opts_setwerror(const char *name, bool on)
{
    return opts_setflag_all(name, on, opts.werror, opts_warn_list, COUNT_WARNINGS);
}
bool opts_setoptim(const char *name, bool on)
{
    return opts_setflag_all(name, on, opts.optimization, opts_opt_list, COUNT_OPTIMIZATIONS);
}

void opts_set(uint32_t *flags, size_t idx, bool on)
{
    LongBit lb;
    LONGBIT_SET(lb, idx);
    if (on)
        flags[lb.idx] |= (1u<<(lb.bit));
    else
        flags[lb.idx] &= ~(1u<<(lb.bit));
}
void opts_setoptimlevel(unsigned int level)
{
    size_t i;
    for(i = 0; i < COUNT_OPTIMIZATIONS; ++i)
        opts_set(opts.optimization, i, level >= opts_opt_oflag[i]);
    if (!level)
        opts.optimizeoff = true;
}

/*
 * Standard configuration parser and subsystem.  Yes, optionally you may
 * create ini files or cfg (the driver accepts both) for a project opposed
 * to supplying just a progs.src (since you also may need to supply command
 * line arguments or set the options of the compiler) [which cannot be done
 * from a progs.src.
 */

 /*
 * returns true/false for a char that contains ("true" or "false" or numeric 0/1)
 */
static bool opts_ini_bool(const char *value)
{
    if (!strcmp(value, "true")) return true;
    if (!strcmp(value, "false")) return false;
    return !!strtol(value, nullptr, 10);
}

// undef all
#undef MAKIC_DEFINE_FLAGS
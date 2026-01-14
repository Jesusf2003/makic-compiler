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

// undef all
#undef MAKIC_DEFINE_FLAGS
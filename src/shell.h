#include "common.h"
#include <io.h>
#include <string.h>

namespace shell
{
    struct Command
    {
        char name[64];
        void (*function)(int argc, char **argv);
    };

    inline static Command cmdList[MAX_COMMANDS];
    inline static int cmdCount = 0;

    void addCmd(const char *name, void (*function)(int argc, char **argv));
    void execCmd(char *input);
}
#include <io.h>
#include <string.h>

#define MAX_COMMANDS    128

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
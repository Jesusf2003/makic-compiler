namespace cmd
{
    extern int cargc;
    extern char **cargv;

    int checkNextCommand(const char *check, int last);
    int checkCommand(const char *cmd);
}
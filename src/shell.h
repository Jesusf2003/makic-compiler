namespace shell
{
    void addCmd(char *name, void (*function)(int argc, char **argv));
    void execCmd(char *input);
}
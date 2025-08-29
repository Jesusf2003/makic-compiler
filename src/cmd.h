namespace cmd
{
    void addCommand(char* name, void (*function)(int argc, char** argv));

    void execCommand(char* input);
}
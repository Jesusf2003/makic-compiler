#include "cmdlib.h"

#define PATH_SEPARATOR '/'

namespace cmdlib
{
    int checkParm(char *check)
    {
        for (int i = 1; i < cargc; i++)
        {
            if (!strcasecmp(check, cargv[i]))
            {
                return i;
            }
        }
        return 0;
    }

    void getWorkdir(char *out)
    {
#ifdef WIN32
        getcwd(out, 256);
        strcat(out, "\\");
#else
        getwd(out);
#endif
    }

    void makeDir(char *path)
    {
#ifdef WIN32
        if (_mkdir(path) == 0)
            return;
#else
        if (mkdir(path, 0777) == 0)
            return;
#endif
        if (errno != EEXIST)
        {
            std::cerr << "mkdir: " << path << "\n"
                      << strerror(errno);
        }
    }

    char currentDir[1024] = {0};
    char gamedir[1024];
    void setDirFromPath(char *path)
    {
        if (!path || !*path)
        {
            currentDir[0] = '\0';
            return;
        }
        const char* lastSlash = strrchr(path, '/');
        #ifdef WIN32
            const char* lastBackslash = strrchr(path, '\\');
            if (lastBackslash && (!lastSlash || lastBackslash > lastSlash))
            {
                lastSlash = lastBackslash;
            }
        #endif
        if (lastSlash)
        {
            size_t len = lastSlash - path;
            if (len >= sizeof(currentDir)) len = sizeof(currentDir) - 1;
            strncpy(currentDir, path, len);
            currentDir[len] = '\0';
        } else {
            strcpy(currentDir, ".");
        }
    }

    char *expandPath(char *path)
    {
        static char full[1024];
        if (currentDir[0] == '\0')
        {
            std::cerr << "Expand path was called without current dir set\n";
            return nullptr;
        }
        if (path[0] == '/' || path[0] == '\\' || (path[1] == ':')) return const_cast<char*>(path);
        snprintf(full, sizeof(full), "%s/%s", currentDir, path);
        return full;
    }

    // utils
    int strncasecmp(const char *s1, const char *s2, int n)
    {
        if (n <= 0)
            return 0;
        while (n-- && *s1 && *s2)
        {
            char c1 = std::toupper(*s1++);
            char c2 = std::toupper(*s2++);
            if (c1 != c2)
                return c1 - c2;
        }
        if (n < 0)
            return 0;
        return std::toupper(*s1) - std::toupper(*s2);
    }

    int strcasecmp(char *s1, char *s2)
    {
        return strncasecmp(s1, s2, 99999);
    }

    char *strToUpper(char *start)
    {
        char *in = start;
        while (*in)
        {
            *in = std::toupper(*in);
            in++;
        }
        return start;
    }

    char *strtoLower(char *start)
    {
        char *in = start;
        while (*in)
        {
            *in = std::tolower(*in);
            in++;
        }
        return start;
    }
}
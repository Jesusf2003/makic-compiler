#include "cmdlib.h"

#define PATH_SEPARATOR '/'
#define MAX_PATH 260

namespace fs = std::filesystem;

namespace cmdlib
{
    int cargc;
    char **cargv;
    bool archive;
    char archivedir[1024];

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
        const char *lastSlash = strrchr(path, '/');
#ifdef WIN32
        const char *lastBackslash = strrchr(path, '\\');
        if (lastBackslash && (!lastSlash || lastBackslash > lastSlash))
        {
            lastSlash = lastBackslash;
        }
#endif
        if (lastSlash)
        {
            size_t len = lastSlash - path;
            if (len >= sizeof(currentDir))
                len = sizeof(currentDir) - 1;
            strncpy(currentDir, path, len);
            currentDir[len] = '\0';
        }
        else
        {
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
        if (path[0] == '/' || path[0] == '\\' || (path[1] == ':'))
            return const_cast<char *>(path);
        snprintf(full, sizeof(full), "%s/%s", currentDir, path);
        return full;
    }

    void defaultExt(char *path, char *ext, size_t bufsize)
    {
        size_t len = strlen(path);
        if (len == 0)
        {
            strncat(path, ext, bufsize - 1);
            return;
        }
        char *src = path + len - 1;
        while (src > path && *src != PATH_SEPARATOR)
        {
            if (*src == '.')
            {
                return;
            }
            src--;
        }
        if (len + strlen(ext) < bufsize)
        {
            strcat(path, ext);
        }
    }

    void defaultPath(char *path, size_t pathSize, char *basepath)
    {
        char temp[MAX_PATH];
        if (path[0] == PATH_SEPARATOR)
        {
            return;
        }
        strncpy(temp, path, sizeof(temp) - 1);
        temp[sizeof(temp) - 1] = '\0';
        snprintf(path, pathSize, "%s%s", basepath, temp);
    }

    char *expandPathAndArchive(char *path)
    {
        char *expanded = expandPath((char *)path);
        if (archive)
        {
            char archivename[1024];
            snprintf(archivename, sizeof(archivename), "%s/%s", archivedir, path);
            copyFile(expanded, archivename);
        }
        return expanded;
    }

    void stripFilename(char *path)
    {
        int length = strlen(path);
        for (int i = length - 1; i >= 0; i--)
        {
            if (path[i] == '/' || path[i] == '\\')
            {
                path[i + 1] = '\0';
                return;
            }
        }
    }

    void stripExt(char *path)
    {
        int length = strlen(path);
        for (int i = length - 1; i >= 0; i--)
        {
            if (path[i] == '.')
            {
                path[i] = '\0';
                return;
            }
            if (path[i] == '/' || path[i] == '\\')
            {
                break;
            }
        }
    }

    void extractFilePath(const char *path, char *dest, size_t destSize)
    {
        const char *lastSlash = strrchr(path, '/');
        const char *lastBack = strrchr(path, '\\');
        const char *sep = (lastSlash > lastBack) ? lastSlash : lastBack;
        if (sep)
        {
            size_t len = sep - path + 1;
            if (len >= destSize)
                len = destSize - 1;
            strncpy(dest, path, len);
            dest[len] = '\0';
        }
        else
        {
            dest[0] = '\0';
        }
    }

    void extractFileBase(const char *path, char *dest, size_t destSize)
    {
        const char *lastSlash = strrchr(path, '/');
        const char *lastBack = strrchr(path, '\\');
        const char *sep = (lastSlash > lastBack) ? lastSlash : lastBack;

        const char *filename = sep ? sep + 1 : path;
        const char *dot = strrchr(filename, '.');

        size_t len = dot ? (size_t)(dot - filename) : strlen(filename);
        if (len >= destSize)
            len = destSize - 1;

        strncpy(dest, filename, len);
        dest[len] = '\0';
    }

    void extractFileExt(const char *path, char *dest, size_t destSize)
    {
        const char *dot = strrchr(path, '.');
        if (dot && dot[1] != '\0')
        {
            strncpy(dest, dot + 1, destSize - 1);
            dest[destSize - 1] = '\0';
        }
        else
        {
            dest[0] = '\0';
        }
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

    void createPath(const char *path)
    {
        fs::path p(path);
        if (!fs::exists(p.parent_path()))
        {
            fs::create_directories(p.parent_path());
        }
    }

    void copyFile(char *from, char *to)
    {
        void *buffer;
        int length;

        // abrir archivo origen
        FILE *f = fopen(from, "rb");
        if (!f)
            return;

        fseek(f, 0, SEEK_END);
        length = ftell(f);
        rewind(f);

        buffer = malloc(length);
        fread(buffer, 1, length, f);
        fclose(f);

        // crear carpeta destino (muy básico)
        makeDir(to);

        // guardar archivo destino
        FILE *g = fopen(to, "wb");
        if (g)
        {
            fwrite(buffer, 1, length, g);
            fclose(g);
        }

        free(buffer);
    }
}
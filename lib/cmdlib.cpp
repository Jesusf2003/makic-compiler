#include "cmdlib.h"
#include <utility>
#include <cstring>

namespace cmdlib
{
    FileBuffer loadFile(const char* path) // returns file buffer data
    {
        FileBuffer fb;                  // open file
        FILE *f = fopen(path, "rb");
        if (!f) return fb;

        if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return fb; }   // Search into the file
        long size = ftell(f);
        if (size < 0) { fclose(f); return fb; }
        rewind(f);

        fb.length = static_cast<int>(size); // obtain the file size
        fb.data = (unsigned char*)malloc(fb.length);
        if (!fb.data) { fclose(f); fb.length = 0; return fb; }

        size_t read = fread(fb.data, 1, fb.length, f);  // reads content
        fclose(f);
        if (read != static_cast<size_t>(fb.length))
        {
            free(fb.data);
            fb.data = nullptr;
            fb.length = 0;
        }
        return fb;
    }

    bool saveFile(const char *path, const unsigned char *data, int length)
    {
        FILE *f = fopen(path, "wb");
        if (!f) return false;
        size_t written = fwrite(data, 1, length, f);
        fclose(f);
        return written == static_cast<size_t>(length);
    }

    bool copyFile(const char *from, const char *to) {
        FileBuffer fb = loadFile(from);
        if(!fb.data) return false;
        return saveFile(to, fb.data, fb.length);
    }

    bool deleteFile(const char *path)
    {
        return std::remove(path) == 0;
    }
}
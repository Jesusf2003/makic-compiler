#include "cmdlib.h"
#include <utility>
#include <cstring>

namespace cmdlib
{
    FileBuffer loadFile(const char* path)
    {
        FileBuffer fb;
        FILE *f = fopen(path, "rb");
        if (!f) return fb;

        if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return fb; }
        long size = ftell(f);
        if (size < 0) { fclose(f); return fb; }
        rewind(f);

        fb.length = static_cast<int>(size);
        fb.data = (unsigned char*)malloc(fb.length);
        if (!fb.data) { fclose(f); fb.length = 0; return fb; }

        size_t read = fread(fb.data, 1, fb.length, f);
        fclose(f);
        if (read != static_cast<size_t>(fb.length))
        {
            free(fb.data);
            fb.data = nullptr;
            fb.length = 0;
        }
        return fb;
    }
}
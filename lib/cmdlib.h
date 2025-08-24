#ifndef CMDLIB_H
#define CMDLIB_H

#include <memory>
#include <string>

#include <cstdlib>
#include <cstddef>
#include <cstdio>

namespace cmdlib
{
    
    struct FileBuffer
    {
        unsigned char *data;
        int length;

        FileBuffer() : data(nullptr), length(0) {}

        ~FileBuffer()
        {
            if (data)
                free(data);
        }

        // delete copy
        FileBuffer(const FileBuffer &) = delete;
        FileBuffer &operator=(const FileBuffer &) = delete;

        // move constructor
        FileBuffer(FileBuffer &&other) noexcept
        {
            data = other.data;
            length = other.length;
            other.data = nullptr;
            other.length = 0;
        }

        // move assignment
        FileBuffer &operator=(FileBuffer &&other) noexcept
        {
            if (this != &other)
            {
                if (data)
                    free(data);
                data = other.data;
                length = other.length;
                other.data = nullptr;
                other.length = 0;
            }
            return *this;
        }
    };
    
    // file movements
    FileBuffer loadFile(const char* path);
    bool saveFile(const char *path, const unsigned char *data, int length);
    bool copyFile(const char *from, const char *to);
    bool deleteFile(const char *path); // Maybe unneccessary
}

#endif
#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct StringList
{
    char* data;
    struct StringList* next;
} StringList;

typedef struct TextBuffer
{
    char** lines;
    int lines_count;
} TextBuffer;

TextBuffer read_file(const char* filename);
void panic(const char* format, ...);

#define assert(expr, format, ...) do { if (!(expr)) panic(format, __VA_ARGS__); } while (0)

#endif

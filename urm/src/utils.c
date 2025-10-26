#include "../utils.h"

#include <stdarg.h>
#include <string.h>

#define ERROR_ALLOC_MSG "can't alloc memory for a string while reading a file %s", filename

TextBuffer read_file(const char* filename)
{
    FILE* file = fopen(filename, "r");
    assert(file != NULL, "can't open a file: %s", filename);

    StringList* head = NULL;
    StringList* tail = NULL;

    char line[128];
    int lines_count = 0;

    while (fgets(line, sizeof(line), file))
    {
        StringList* node = malloc(sizeof(StringList));
        assert(node != NULL, ERROR_ALLOC_MSG);

        node->data = _strdup(line);
        assert(node->data != NULL, ERROR_ALLOC_MSG);

        node->next = NULL;

        if (head == NULL)
        {
            head = node;
            tail = node;
        }
        else
        {
            tail->next = node;
            tail = node;
        }

        lines_count++;
    }

    fclose(file);

    TextBuffer tb = {
        .lines_count = lines_count,
        .lines = malloc(sizeof(char*) * lines_count)
    };

    assert(tb.lines != NULL, ERROR_ALLOC_MSG);

    StringList* current = head;

    for (int i = 0; i < lines_count; i++)
    {
        tb.lines[i] = current->data;
        StringList* old = current;
        current = current->next;
        free(old);
    }

    return tb;
}

void panic(const char* format, ...)
{
    va_list list;
    va_start(list, format);

    fprintf(stderr, "[URM Error]: ");
    vfprintf(stderr, format, list);

    va_end(list);

    exit(1);
}

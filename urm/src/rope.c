#include "../rope.h"
#include "../utils.h"

#include <stdlib.h>

int* rope_get(Rope* rope, int index)
{
    if (!rope)
        return NULL;

    if (rope->length <= index)
    {
        int start = rope->length;
        rope->length = index + 1;

        int* new_data = (int*)realloc(rope->data, rope->length * sizeof(int));

        if (new_data == NULL)
            panic("could not shrink a rope");
        
        rope->data = new_data;
        
        while (start < rope->length)
        {
            rope->data[start] = 0;
            start++;
        }
    }

    return rope->data + index;
}

void rope_set(Rope* rope, int index, int value)
{
    *rope_get(rope, index) = value;
}

void rope_clear(Rope* rope)
{
    rope->length = 0;
    free(rope->data);
}

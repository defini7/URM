#ifndef ROPE_H
#define ROPE_H

typedef struct Rope
{
    int* data;
    int length;
} Rope;

int* rope_get(Rope* rope, int index);
void rope_set(Rope* rope, int index, int value);

void rope_clear(Rope* rope);

#endif

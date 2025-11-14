/*---------------------------------------------------------------------------------------------
 *  Copyright 2025 defini7. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/

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

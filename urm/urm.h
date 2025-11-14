/*---------------------------------------------------------------------------------------------
 *  Copyright 2025 defini7. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/

#ifndef URM_H
#define URM_H

#include "rope.h"
#include "utils.h"

#include <stdbool.h>

// If you change the order of these
// then change the order of values in MAX_ARGS
typedef enum UrmParseInstruction
{
    Ps_Inst_Z,
    Ps_Inst_S,
    Ps_Inst_T,
    Ps_Inst_J
} UrmParseInstruction;

typedef struct UrmLine
{
    UrmParseInstruction inst;
    int args[3];
} UrmLine;

typedef struct UrmLinesNode
{
    UrmLine data;
    struct UrmLinesNode* next;
} UrmLinesNode;

typedef struct UrmLines
{
    UrmLine* data;
    int count;
} UrmLines;

// The order is reserved because we index it with UrmParseInstruction enum values
static const int MAX_ARGS[] = { 1, 1, 2, 3 };

typedef struct UrmParseState
{
    UrmLinesNode* lines;

    // Pointer to the currently being constructed line from lines
    UrmLinesNode** cur_line;

    // Length of the lines array
    int lines_count;

    // State that must be evaluated
    enum
    {
        Ps_NewInst,
        Ps_NextArg,
        Ps_ParseArg,
        Ps_MoveToNextLine
    } state;

    // Number of arguments that were parsed on the current instruction
    int args_read;

    // Buffer for storing an argument
    char num[20];
    int num_index;

    // Currently being parsed character
    char cur_char;
} UrmParseState;

typedef struct UrmExecState
{
    Rope* rope;
    const UrmLine* line;
    int next_line;
} UrmExecState;

// These work only for ASCII characters
char urm__to_lower(char c);

inline bool urm__is_space(char c);
inline bool urm__is_numeric(char c);

void urm__exec_inst(UrmExecState* es);
int urm__on_char_parse(UrmParseState* ps);

UrmLines urm_parse(const TextBuffer* code);
void urm_exec(const UrmLines lines, Rope* rope, int max_insts);

void urm_do_raw(const TextBuffer* code, Rope* rope, int max_insts);
void urm_do_file(const char* filename, Rope* rope, int max_insts);

#endif

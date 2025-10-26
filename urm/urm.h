#ifndef URM_H
#define URM_H

#include "rope.h"
#include "utils.h"

#include <stdbool.h>

typedef enum ParseState
{
    Ps_NewInst,
    Ps_NextArg,
    Ps_ParseArg,
    Ps_MoveToNextLine
} ParseState;

// If you change the order of these
// then change the order of values in MAX_ARGS
typedef enum ParseInstruction
{
    Ps_Inst_Z,
    Ps_Inst_S,
    Ps_Inst_T,
    Ps_Inst_J
} ParseInstruction;

// The order is reserved because we index it with ParseInstruction values
static const int MAX_ARGS[] = { 1, 1, 2, 3 };

typedef struct EvalState
{
    // State that must be evaluated
    ParseState state;

    // Currently being parsed instruction
    ParseInstruction inst;

    Rope* rope;

    // Number of arguments that were parsed on the current instruction
    int args_read;

    char num[20];
    int num_index;
    
    // Maximum 3 arguments
    int args[3];

    char cur_char;
    int next_line;
} ExecState;

char urm__to_lower(char c);

inline bool urm__is_space(char c);
inline bool urm__is_numeric(char c);

void urm__exec_inst(ExecState* es);
ParseState urm__on_char_parse(ExecState* es);

void urm_exec(Rope* rope, const TextBuffer* code);

#endif

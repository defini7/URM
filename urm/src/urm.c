/*---------------------------------------------------------------------------------------------
 *  Copyright 2025 defini7. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/

#include "../urm.h"
#include <string.h>

#define ERROR_ALLOC_MSG "can't alloc memory for an instruction while parsing code"

char urm__to_lower(char c)
{
    if ('A' <= c && c <= 'Z')
        return c + (char)32;

    return c;
}

inline bool urm__is_space(char c)
{
    return c == ' ' || c == '\t' || c == '\b' || c == '\n' || c == '\r';
}

inline bool urm__is_numeric(char c)
{
    return '0' <= c && c <= '9';
}

void urm__exec_inst(UrmExecState* es)
{
    UrmLine* line = es->line;

    switch (line->inst)
    {
    case Ps_Inst_Z:
    {
        rope_set(es->rope, line->args[0], 0);
        es->next_line++;
    }
    break;

    case Ps_Inst_S:
    {
        int value = *rope_get(es->rope, line->args[0]) + 1;

        rope_set(es->rope, line->args[0], value);

        es->next_line++;
    }
    break;

    case Ps_Inst_T:
    {
        int src = *rope_get(es->rope, line->args[0]);
        rope_set(es->rope, line->args[1], src);

        es->next_line++;
    }
    break;
    
    case Ps_Inst_J:
    {
        int first = *rope_get(es->rope, line->args[0]);
        int second = *rope_get(es->rope, line->args[1]);

        if (first == second)
            es->next_line = line->args[2] - 1;
        else
            es->next_line++;
    }
    break;

    }
}

int urm__on_char_parse(UrmParseState* ps)
{
    char c = ps->cur_char;
    UrmLine* cur_line = &(*ps->cur_line)->data;

    switch (ps->state)
    {
    case Ps_NewInst:
    {
        if (urm__is_space(c))
            return Ps_NewInst;

        char c1 = urm__to_lower(c);

        switch (c1)
        {
        case 'z': cur_line->inst = Ps_Inst_Z; break;
        case 's': cur_line->inst = Ps_Inst_S; break;
        case 't': cur_line->inst = Ps_Inst_T; break;
        case 'j': cur_line->inst = Ps_Inst_J; break;
        default: panic("invalid instruction: %c", c);
        }

        return Ps_NextArg;
    }
    break;

    case Ps_NextArg:
    {
        if (urm__is_space(c))
            return Ps_NextArg;

        if (urm__is_numeric(c))
        {
            ps->num_index = 0;
            ps->num[0] = c;
            return Ps_ParseArg;
        }

        panic("argument is not a numeric value");
    }
    break;

    case Ps_ParseArg:
    {
        if (urm__is_space(c))
        {
            int d = 1;
            for (int i = ps->num_index; i >= 0; i--, d *= 10)
                cur_line->args[ps->args_read] += (int)(ps->num[i] - '0') * d;

            ps->args_read++;

            if (ps->args_read >= MAX_ARGS[cur_line->inst])
            {
                ps->args_read = 0;
                ps->lines_count++;

                return Ps_MoveToNextLine;
            }

            return Ps_NextArg;
        }

        if (!urm__is_numeric(c))
            panic("arguments must be numeric values, not: %c", c);

        ps->num[ps->num_index] = c;
        return Ps_ParseArg;
    }
    break;

    }

    return Ps_MoveToNextLine;
}

UrmLines urm_parse(const TextBuffer* code)
{
    UrmParseState ps = {0};
    ps.cur_line = &ps.lines;

    for (int i = 0; i < code->lines_count; i++)
    {
        ps.state = Ps_NewInst;

        *ps.cur_line = calloc(1, sizeof(UrmLinesNode));
        assert(*ps.cur_line != NULL, ERROR_ALLOC_MSG);

        int len = strlen(code->lines[i]);

        for (int j = 0; j <= len && ps.state != Ps_MoveToNextLine; j++)
        {
            ps.cur_char =
                (j == len) ? ' ' :
                code->lines[i][j];

            ps.state = urm__on_char_parse(&ps);
        }

        ps.cur_line = &(*ps.cur_line)->next;
    }

    UrmLines lines = {
        .data=malloc(sizeof(UrmLine) * ps.lines_count),
        .count=ps.lines_count
    };

    assert(lines.data != NULL, ERROR_ALLOC_MSG);

    UrmLinesNode* line = ps.lines;

    for (int i = 0; line != NULL; i++)
    {
        lines.data[i] = line->data;
        line = line->next;
    }

    return lines;
}

void urm_exec(const UrmLines lines, Rope* rope, int max_insts)
{
    UrmExecState es = {0};
    es.rope = rope;

    for (int i = 0; es.next_line < lines.count && i < max_insts; i++)
    {
        es.line = &lines.data[es.next_line];
        urm__exec_inst(&es);
    }
}

void urm_do_raw(const TextBuffer* code, Rope* rope, int max_insts)
{
    const UrmLines lines = urm_parse(code);
    
    urm_exec(lines, rope, max_insts);
}

void urm_do_file(const char* filename, Rope* rope, int max_insts)
{
    const TextBuffer code = read_file(filename);
    const UrmLines lines = urm_parse(&code);

    urm_exec(lines, rope, max_insts);
}

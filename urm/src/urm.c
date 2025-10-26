#include "../urm.h"

#include <string.h>

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

void urm__exec_inst(ExecState* es)
{
    if (es->inst == Ps_Inst_Z)
    {
        rope_set(es->rope, es->args[0], 0);
        es->next_line++;
    }
    else if (es->inst == Ps_Inst_S)
    {
        int value = *rope_get(es->rope, es->args[0]) + 1;

        rope_set(es->rope, es->args[0], value);

        es->next_line++;
    }
    else if (es->inst == Ps_Inst_T)
    {
        int src = *rope_get(es->rope, es->args[0]);
        rope_set(es->rope, es->args[1], src);

        es->next_line++;
    }
    else if (es->inst == Ps_Inst_J)
    {
        int first = *rope_get(es->rope, es->args[0]);
        int second = *rope_get(es->rope, es->args[1]);

        if (first == second)
            es->next_line = es->args[2] - 1;
        else
            es->next_line++;
    }
}

ParseState urm__on_char_parse(ExecState* es)
{
    char c = es->cur_char;

    switch (es->state)
    {
    case Ps_NewInst:
    {
        if (urm__is_space(c))
            return Ps_NewInst;

        char c1 = urm__to_lower(c);

        switch (c1)
        {
        case 'z': es->inst = Ps_Inst_Z; break;
        case 's': es->inst = Ps_Inst_S; break;
        case 't': es->inst = Ps_Inst_T; break;
        case 'j': es->inst = Ps_Inst_J; break;
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
            es->num_index = 0;
            es->num[0] = c;
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
            for (int i = es->num_index; i >= 0; i--, d *= 10)
                es->args[es->args_read] += (int)(es->num[i] - '0') * d;

            es->args_read++;

            if (es->args_read >= MAX_ARGS[es->inst])
            {
                urm__exec_inst(es);
                
                for (int i = 0; i < es->args_read; i++)
                    es->args[i] = 0;

                es->args_read = 0;

                return Ps_MoveToNextLine;
            }

            return Ps_NextArg;
        }

        if (!urm__is_numeric(c))
            panic("arguments must be numeric values, not: %c", c);

        es->num[es->num_index] = c;
        return Ps_ParseArg;
    }
    break;

    }
}

void urm_exec(Rope* rope, const TextBuffer* code)
{
    ExecState es = {0};
    es.rope = rope;

    while (es.next_line < code->lines_count)
    {
        es.state = Ps_NewInst;

        int len = strlen(code->lines[es.next_line]);
        
        for (int i = 0; i <= len && es.state != Ps_MoveToNextLine; i++)
        {
            es.cur_char =
                (i == len) ? ' ' :
                code->lines[es.next_line][i];

            es.state = urm__on_char_parse(&es);
        }
    }
}

#include "instruction.h"

EMITTER_API void
emit_file_top(emit_t *obj)
{
    fprintf(
        obj->target,
        "section .text"
        "\n\tglobal %s"
        "\n\n",
        obj->entry_point);
}

EMITTER_API void
emit_label_instruction(
    emit_t *obj,
    char *lab)
{
    fprintf(
        obj->target,
        "_%s:",
        lab);
}

EMITTER_API void
emit_mov_instruction(
    emit_t *obj,
    char *reg,
    char *val)
{
    fprintf(
        obj->target,
        "\n\tmov %s, %s",
        reg, val);
}

EMITTER_API void
emit_push_instruction(
    emit_t *obj,
    char *val)
{
    fprintf(
        obj->target,
        "\n\tpush %s",
        !!val ? val : "");
}

EMITTER_API void
emit_bare_asm(
    emit_t *obj,
    char *fmt,
    ...)
{
    va_list vl;
    va_start(vl, fmt);

    char *rstr = MALLOC(sizeof(char));
    int rsc = 0, fmtl = strlen(fmt);
    size_t i = 0;

    while (i < fmtl)
    {
        char c = fmt[i];

        if (c == '%')
        {
            char nxt = fmt[i + 1];

            switch (nxt)
            {
            case 'd':
            {
                double d = va_arg(vl, double);

                rstr = REALLOC(rstr, (rsc + 32) * sizeof(char));
                rstr[rsc] = '\0';
                sprintf(rstr, "%s%d", rstr, d);

                rsc = strlen(rstr);
                rstr = REALLOC(rstr, rsc * sizeof(char));
            }
            break;
            case 'i':
            {
                int d = va_arg(vl, int);

                rstr = REALLOC(rstr, (rsc + 32) * sizeof(char));
                rstr[rsc] = '\0';
                sprintf(rstr, "%s%i", rstr, d);

                rsc = strlen(rstr);
            }
            break;
            case 's':
            {
                char *d = va_arg(vl, char *);
                int dl = strlen(d);

                rstr = REALLOC(rstr, (rsc + dl) * sizeof(char));
                rstr[rsc] = '\0';
                sprintf(rstr, "%s%s", rstr, d);

                rsc = strlen(rstr);
            }
            break;

            default:
                break;
            }

            i++;
        }
        else
        {
            if (rsc)
                rstr = REALLOC(rstr, (rsc + 1) * sizeof(char));
            rstr[rsc++] = c;
        }

        i++;
    }

    if (rsc)
        rstr = REALLOC(rstr, (rsc + 1) * sizeof(char));
    rstr[rsc++] = '\0';

    fprintf(
        obj->target,
        "\n\t%s",
        rstr);

    va_end(vl);
}
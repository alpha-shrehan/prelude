#include "debug.h"
#include "structs.h"

JIT_API void
Debug_PrintBreakPoint(
    const char *file_name,
    const char *func_name,
    int line_number)
{
    printf("[debug] In file %s in function %s at line %d\n",
           file_name,
           func_name,
           line_number);
}

JIT_API void
Debug_PrintJITToken(FILE *fs, void *t)
{
    struct _jit_token_str *tok = (struct _jit_token_str *)t;

    switch (tok->type)
    {
    case JIT_TOKEN_CHAR:
        fprintf(fs, "[debug] (char) %c\n", tok->v.Char.val);
        break;
    case JIT_TOKEN_FLOAT:
        fprintf(fs, "[debug] (float) %f\n", tok->v.Float.val);
        break;
    case JIT_TOKEN_IDENTIFIER:
        fprintf(fs, "[debug] (identifier) [dt: %d, tt: %d] %s\n", tok->v.Identifier.reserved_data_type, tok->v.Identifier.reserved_token, tok->v.Identifier.val);
        break;
    case JIT_TOKEN_INTEGER:
        fprintf(fs, "[debug] (int) %d\n", tok->v.Integer.val);
        break;
    case JIT_TOKEN_NEWLINE:
        fprintf(fs, "[debug] newline\n");
        break;
    case JIT_TOKEN_OPERATOR:
        fprintf(fs, "[debug] (operator) %s\n", tok->v.Operator.val);
        break;
    case JIT_TOKEN_STRING:
        fprintf(fs, "[debug] (string) %s\n", tok->v.String.val);
        break;
    
    default:
        fprintf(fs, "[debug] Unknown token\n");
        break;
    }
}
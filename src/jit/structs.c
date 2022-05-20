#include "structs.h"

char *RESERVED_TOKENS[] = {
    "if", "else", "loop", "decl", NULL};

char *RESERVED_DTYPES[] = {
    "int", "char", "bool", NULL};

char *_make_op(char, char, char);

JIT_API struct _jit_lexer_ctx_str *
Jit_Lexer_Context_New(char *data)
{
    struct _jit_lexer_ctx_str *ctx = MALLOC(sizeof(struct _jit_lexer_ctx_str));
    ctx->cpos = 0;
    ctx->raw = data;
    ctx->tok_count = 0;
    ctx->tok_limit = 32;
    ctx->toks = MALLOC(ctx->tok_limit * sizeof(struct _jit_token_str));
}

void _add_token(
    struct _jit_lexer_ctx_str *ctx,
    struct _jit_token_str tok)
{
    if (ctx->tok_count == ctx->tok_limit)
    {
        ctx->tok_limit <<= 1;
        ctx->toks = REALLOC(
            ctx->toks,
            (ctx->tok_limit) * sizeof(struct _jit_token_str));
    }

    ctx->toks[ctx->tok_count++] = tok;
}

void _resize_toks(
    struct _jit_lexer_ctx_str *ctx)
{
    if (abs(ctx->tok_count - ctx->tok_limit) < 16)
        return;

    ctx->tok_limit = 32;
    while (ctx->tok_count > ctx->tok_limit)
        ctx->tok_limit <<= 1;
}

JIT_API void
Jit_Lexer_Initialize(struct _jit_lexer_ctx_str *ctx)
{
    int rlen = strlen(ctx->raw),
        i = 0;

    while (i < rlen)
    {
        char r = ctx->raw[i];

        if (isalpha(r))
        {
            char var[IDENTIFIER_LENGTH_LIMIT];
            var[0] = r;
            var[1] = '\0';

            for (size_t j = i + 1; j < rlen; j++)
            {
                if (isalnum(ctx->raw[j]))
                    strcat(var, (char[]){ctx->raw[j], '\0'});
                else
                {
                    i = j - 1;
                    break;
                }
            }

            _add_token(ctx, (struct _jit_token_str){
                                .type = JIT_TOKEN_IDENTIFIER,
                                .v.Identifier = {
                                    .reserved_token = Ut_String_In_StringArray(RESERVED_TOKENS, var),
                                    .reserved_data_type = Ut_String_In_StringArray(RESERVED_DTYPES, var),
                                    .val = strdup(var)}});

            goto end;
        }

        if (strstr("~!%^&*()-+=[]{}\\|;:,.<>/?", (char[]){r, '\0'}) != NULL)
        {
            char c1 = r, c2, c3;

            if (i < rlen - 1)
                c2 = ctx->raw[i + 1];
            if (i < rlen - 2)
                c3 = ctx->raw[i + 2];

            _add_token(ctx, (struct _jit_token_str){
                                .type = JIT_TOKEN_OPERATOR,
                                .v.Operator = {
                                    .val = _make_op(c1, c2, c3)}});

            i += strlen(ctx->toks[ctx->tok_count - 1].v.Operator.val);
            continue;
        }

        if (isdigit(r))
        {
            char num[NUMBER_LENGTH_LIMIT];
            num[0] = r;
            int oi = i;

            while (strstr("123456789.0", (char[]){ctx->raw[++i], '\0'}) != NULL)
                num[i - oi] = ctx->raw[i - 1];

            num[i - oi] = '\0';

            bool is_float = !!strstr(num, ".");

            if (is_float)
                _add_token(ctx, (struct _jit_token_str){
                                    .type = JIT_TOKEN_FLOAT,
                                    .v.Float = {
                                        .val = atof(num)}});
            else
                _add_token(ctx, (struct _jit_token_str){
                                    .type = JIT_TOKEN_INTEGER,
                                    .v.Integer = {
                                        .val = atoi(num)}});

            continue;
        }

        switch (r)
        {
        case '\n':
            _add_token(ctx, (struct _jit_token_str){
                                .type = JIT_TOKEN_NEWLINE});
            break;

        default:
            break;
        }

    end:
        i++;
    }

    _resize_toks(ctx);
}

char *_make_op(char c1, char c2, char c3)
{
    char op[4];
    memset(op, 0, 4 * sizeof(char));

    switch (c1)
    {
    case '*':
    case '/':
    case '%':
    case '^':
    case '&':
    case '|':
    case '=':
    case '!':
    {
        op[0] = c1;
        if (c2 == '=')
            op[1] = c2;
    }
    break;
    case '+':
    case '<':
    case '>':
    {
        op[0] = c1;
        if (c2 == c1 ||
            c2 == '=')
            op[1] = c2;

        if ((c1 == '<' ||
             c1 == '>') &&
            c2 == c1)
            if (c3 == '=')
                op[2] = c3;
    }
    break;
    case '-':
    {
        op[0] = c1;
        if (c2 == c1 ||
            c2 == '=' ||
            c2 == '>')
            op[1] = c2;
    }
    break;
    case ';':
    case ':':
    case '~':
    case '[':
    case ']':
    case '{':
    case '}':
    case '(':
    case ')':
    case '\\':
    case '.':
    case '?':
    case ',':
        op[0] = c1;
        break;

    default:
        break;
    }

    return strdup(op);
}
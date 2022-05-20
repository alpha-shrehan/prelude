#pragma once

#include "Header.h"
#include "debug.h"

enum _jit_token_enum
{
    JIT_TOKEN_INTEGER,
    JIT_TOKEN_FLOAT,
    JIT_TOKEN_OPERATOR,
    JIT_TOKEN_CHAR,
    JIT_TOKEN_STRING,
    JIT_TOKEN_NEWLINE,
    JIT_TOKEN_IDENTIFIER
};

struct _jit_token_str
{
    int type;

    union
    {
        struct
        {
            long long val;
        } Integer;

        struct
        {
            float val;
        } Float;

        struct
        {
            char *val;
        } Operator;

        struct
        {
            char val;
        } Char;

        struct
        {
            char *val;
        } String;

        struct
        {
            bool reserved_token;
            bool reserved_data_type;
            char *val;
        } Identifier;

    } v;
};

struct _jit_lexer_ctx_str
{
    char *raw;
    int cpos;

    struct _jit_token_str *toks;
    int tok_count;
    int tok_limit;
};

#define IDENTIFIER_LENGTH_LIMIT 32
#define NUMBER_LENGTH_LIMIT 32

#if defined(__cplusplus)
extern "C"
{
#endif

    /**
     * @brief New JIT context for lexer.
     * @param data Raw string to parse.
     * @return JIT_API 
     */
    JIT_API struct _jit_lexer_ctx_str *Jit_Lexer_Context_New(char *);

    /**
     * @brief Initialize Lexer for JIT
     * @param ctx Context
     * @return JIT_API 
     */
    JIT_API void Jit_Lexer_Initialize(struct _jit_lexer_ctx_str *);

#if defined(__cplusplus)
}
#endif

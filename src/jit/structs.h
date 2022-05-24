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

#define DEFAULT_TYPE_SIZE 8

enum _jit_expr_const_type
{
    JIT_EXPR_CONSTANT_INT,
    JIT_EXPR_CONSTANT_FLOAT,
    JIT_EXPR_CONSTANT_STRING,
    JIT_EXPR_CONSTANT_VARIABLE,
    JIT_EXPR_CONSTANT_TYPE
};

struct _jit_expr_constant_str
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
        } String;

        struct
        {
            bool isdtype;
            char *val;
        } Variable;

        struct
        {
            bool custom;
            char *val;
        } Type;

    } v;
};

enum _jit_expr_type
{
    JIT_EXPR_CONSTANT,
    JIT_EXPR_FUNC_CALL
};

struct _jit_expr_str
{
    int type;
    int size;

    union
    {
        struct
        {
            struct _jit_expr_constant_str *val;
        } constant;

        struct
        {
            struct _jit_expr_constant_str *name,
                *args;

            int arg_count;
        } func_call;

    } v;
};

enum _jit_stmt_type
{
    JIT_STMT_FUN_DECL,
    JIT_STMT_RETURN
};

struct _jit_stmt_str
{
    int type;

    union
    {
        struct
        {
            char *name;
            struct _jit_expr_str *args,
                *ret_type;
            struct _jit_stmt_str *body;

            int arg_count;
            int body_count;

        } func_decl;

        struct
        {
            struct _jit_expr_str *expr;
        } ret_stmt;

    } v;
};

struct _jit_module_str
{
    char *name;
    struct _jit_stmt_str *body;
    int body_count;
    emit_t *emt;

    struct
    {
        struct
        {
            bool _once;
        } _pragma;

        struct
        {
            char *name;
            char **args;
            char *body;
        } *_macros, _st_sz1;

        int macro_count;
        
    } meta;
};

typedef struct _jit_expr_constant_str jit_const_t;
typedef struct _jit_expr_str jit_expr_t;
typedef struct _jit_stmt_str jit_stmt_t;
typedef struct _jit_module_str jit_module_t;


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

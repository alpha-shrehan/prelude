#pragma once

#include "Header.h"
#include "structs.h"

enum _jit_expr_const_type
{
    JIT_EXPR_CONSTANT_INT,
    JIT_EXPR_CONSTANT_FLOAT,
    JIT_EXPR_CONSTANT_STRING,
    JIT_EXPR_CONSTANT_VARIABLE
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
                ret_type;
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
     * @brief Create a new JIT constant.
     * @param type Type of constant
     * For arguments from [1, n], when type:
     * * float: float
     * * int: int
     * * variable: char *, bool
     * * string: char *
     * @return jit_const_t* 
     */
    JIT_API jit_const_t *Jit_Parser_Const_New(int, ...);

    /**
     * @brief Create a new JIT Expression.
     * @param type Type of expression.
     * Based on the type and elements in a linear order from top to bottom, pass arguments from [1, n]
     * @return jit_expr_t* 
     */
    JIT_API jit_expr_t *Jit_Parser_Expr_New(int, ...);

    /**
     * @brief Create a new JIT Statement.
     * @param type Type of statement.
     * Based on the type and elements in a linear order from top to bottom, pass arguments from [1, n]
     * @return JIT_API* 
     */
    JIT_API jit_stmt_t *Jit_Parser_Stmt_New(int, ...);

    /**
     * @brief Return an empty allocated JIT constant.
     * 
     * @return jit_const_t* 
     */
    JIT_API jit_const_t *Jit_Parser_Empty_Const_New(void);

    /**
     * @brief Return an empty allocated JIT expression.
     * 
     * @return JIT_API* 
     */
    JIT_API jit_expr_t *Jit_Parser_Empty_Expr_New(void);

    /**
     * @brief Return an empty allocated JIT statement.
     * 
     * @return JIT_API* 
     */
    JIT_API jit_stmt_t *Jit_Parser_Empty_Stmt_New(void);

    /**
     * @brief New module for JIT.
     * @param name Name of module
     * @param body Statement body
     * @param body_count Body size of statements array
     * @return jit_module_t* 
     */
    JIT_API jit_module_t *Jit_Parser_Module_New(char *, jit_stmt_t *, int);

#if defined(__cplusplus)
}
#endif

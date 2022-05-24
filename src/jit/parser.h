#pragma once

#include "Header.h"
#include "structs.h"
#include "ast.h"

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

    /**
     * @brief Parse JIT and write object code/asm to file
     * @param mod Module
     * @return JIT_API 
     */
    JIT_API int Jit_Parser_ParseAST(jit_module_t *);

#if defined(__cplusplus)
}
#endif

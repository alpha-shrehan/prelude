#pragma once

#include "Header.h"
#include "structs.h"

#if defined(__cplusplus)
extern "C"
{
#endif

    /**
     * @brief Parse tokens to form AST
     * @param mod Module
     * @param toks Tokens
     * @return int
     */
    JIT_API int Jit_Parser_Make_AST(jit_module_t *, struct _jit_lexer_ctx_str *);

#if defined(__cplusplus)
}
#endif

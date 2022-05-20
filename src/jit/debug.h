#pragma once

#include "Header.h"

#if !defined(MODE_DEBUG)
#   error "'debug.h' is not available in non-debug mode."
#endif

#define dbp Debug_PrintBreakPoint(__FILE__, __FUNCTION__, __LINE__)

#if defined(__cplusplus)
extern "C"
{
#endif

    /**
     * @brief Print a breakpoint's details.
     * @param file_name File name
     * @param func_name Function name
     * @param line_number Line number
     * @return JIT_API 
     */
    JIT_API void Debug_PrintBreakPoint(const char *, const char *, int);

    /**
     * @brief Print a JIT Token
     * @param stream Stream to print to
     * @param t Passed as void *
     * @return JIT_API 
     */
    JIT_API void Debug_PrintJITToken(FILE *, void *);

#if defined(__cplusplus)
}
#endif

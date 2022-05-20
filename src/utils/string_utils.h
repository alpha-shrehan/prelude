#pragma once

#include "Header.h"

#if defined(__cplusplus)
extern "C"
{
#endif

    /**
     * @brief Check if a string exists in a string array.
     * @param arr String array. Must end with NULL
     * @param str String.
     * @return UTILS_API 
     */
    UTILS_API bool Ut_String_In_StringArray(char *[], char *);

#if defined(__cplusplus)
}
#endif

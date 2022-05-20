#include "string_utils.h"

UTILS_API bool 
Ut_String_In_StringArray(char *arr[], char *str)
{
    for (size_t i = 0; !!arr[i]; i++)
        if (!strcmp(arr[i], str))
            return true;
    
    return false;
}
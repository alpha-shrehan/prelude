#include "pmemory.h"
#include "../thread/prthread.h"

PMEMORY_API void *
PMemory_Malloc(size_t size)
{
    void *np = malloc(size);
    return np;
}

PMEMORY_API void *
PMemory_Realloc(void *ptr, size_t nsz)
{
    void *np = realloc(ptr, nsz);
    return np;
}

PMEMORY_API void
PMemory_Free(void *ptr)
{
    free(ptr);
}
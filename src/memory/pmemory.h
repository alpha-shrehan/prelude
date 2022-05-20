#pragma once

/**
 * @file pmemory.h
 * @author Shrehan Raj Singh (shrehanofficial@gmail.com)
 * @brief The Prelude GC works as follows:
 * * Memory allocated is returned as void *, but 
 *   actual block returned is of ```struct _pmem_str *```
 * * .block will have the size allocation.
 * * .size will have size of block.
 * * .flag is to check whether block has been freed.
 * * In case the block is cleared, .flag will have ambiguous value.
 * * Otherwise, the value of flag is always set to 7.
 * @version 0.1
 * @date 2022-05-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Header.h"

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * @brief Malloc implementation for Prelude GC/MA.
     * @param size Size of block.
     * @return PMEMORY_API* 
     */
    PMEMORY_API void *PMemory_Malloc(size_t);

    /**
     * @brief Realloc a block of memory.
     * @param ptr Original block
     * @param nsz New size
     * @return PMEMORY_API* 
     */
    PMEMORY_API void *PMemory_Realloc(void *, size_t);

    /**
     * @brief Free implementation for Prelude GC/MA
     * @param ptr Entity to free
     * @return PMEMORY_API 
     */
    PMEMORY_API void PMemory_Free(void *);

#ifdef __cplusplus
}
#endif

#ifdef MALLOC
#undef MALLOC
#endif

#ifdef CALLOC
#undef CALLOC
#endif

#ifdef REALLOC
#undef REALLOC
#endif

#ifdef FREE
#undef FREE
#endif

#define MALLOC(X) PMemory_Malloc(X)
#define CALLOC(X, Y) calloc(X, Y)
#define REALLOC(X, Y) PMemory_Realloc(X, Y)
#define FREE(X) PMemory_Free(X)

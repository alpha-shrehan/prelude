#pragma once

#include "Header.h"
#include "../memory/pmemory.h"

struct _emitter_str
{
    FILE *target;
    const char *entry_point;

    struct
    {
        struct
        {
            char *buf;
            int bc;
        } bss, text, data;
    } sections;
};

typedef struct _emitter_str emit_t;

#if defined(__cplusplus)
extern "C"
{
#endif
    
    /**
     * @brief Create a new emitter object.
     * @param _target File target
     * @param _entry Entry point
     * @return emit_t* 
     */
    EMITTER_API emit_t *Emit_Emitter_New(const char *, const char *);

    /**
     * @brief Clean an emit object. Destructor
     * @param obj Object
     */
    EMITTER_API void Emit_Clean(emit_t *);

#if defined(__cplusplus)
}
#endif

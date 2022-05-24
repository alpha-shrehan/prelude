#pragma once

#include "Header.h"
#include "structs.h"

#if defined(__cplusplus)
extern "C"
{
#endif

    /**
     * @brief Emit the basic data for top of the file.
     * > This is followed by sections and labels.
     * @param obj Object
     */
    EMITTER_API void emit_file_top(emit_t *);

    /**
     * @brief Emit a label.
     * Adds an underscore before each label name
     * @param obj Object
     * @param lab Label string
     */
    EMITTER_API void emit_label_instruction(emit_t *, char *);

    /**
     * @brief Emit a standard mov instruction
     * @param obj Object
     * @param reg Register to move to
     * @param val Value to move
     */
    EMITTER_API void emit_mov_instruction(emit_t *, char *, char *);

    /**
     * @brief Emit a push instruction
     * @param obj Object
     * @param val Value to push
     */
    EMITTER_API void emit_push_instruction(emit_t *, char *);

    /**
     * @brief Emit bare assembly code.
     * @param obj Object
     * @param fmt Format string
     */
    EMITTER_API void emit_bare_asm(emit_t *, char *, ...);

#if defined(__cplusplus)
}
#endif

#include "structs.h"

EMITTER_API emit_t *
Emit_Emitter_New(
    const char *_target,
    const char *_entry)
{
    emit_t *ne = MALLOC(sizeof(emit_t));

    ne->entry_point = _entry;
    ne->target = fopen(_target, "w+");
    ne->sections.bss.bc = 0;
    ne->sections.bss.buf = MALLOC(sizeof(char));
    ne->sections.text.bc = 0;
    ne->sections.text.buf = MALLOC(sizeof(char));
    ne->sections.data.bc = 0;
    ne->sections.data.buf = MALLOC(sizeof(char));

    return ne;
}

EMITTER_API void Emit_Clean(emit_t *obj)
{
    fclose(obj->target);

    FREE(obj->sections.bss.buf);
    FREE(obj->sections.text.buf);

    obj->sections.bss.bc = 0;
    obj->sections.text.bc = 0;
}
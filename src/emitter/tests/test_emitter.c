#include <emit.h>

int main(int argc, char const *argv[])
{
    emit_t *em = Emit_Emitter_New("../../tests/test.s", "_main");

    emit_file_top(em);
    emit_label_instruction(em, "main");
    emit_mov_instruction(em, "eax", "0");
    emit_push_instruction(em, "eax");

    emit_bare_asm(em, "pop %s", "eax");

    Emit_Clean(em);
    return 0;
}
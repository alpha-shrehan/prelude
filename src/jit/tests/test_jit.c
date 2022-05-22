#include <jit.h>

int main(int argc, char const *argv[])
{
    pfile_t *fp = FileIO_New_withMode("../../tests/test.pc", FMODE_READ);
    struct _jit_lexer_ctx_str *ctx = Jit_Lexer_Context_New(FileIO_ReadWholeFile(fp));;

    Jit_Lexer_Initialize(ctx);

    jit_module_t *mod = Jit_Parser_Module_New("test.pc", NULL, 0);

    Jit_Parser_Make_AST(mod, ctx);

    FileIO_Close(fp);
    return printf("Program Ended.") && 0;
}
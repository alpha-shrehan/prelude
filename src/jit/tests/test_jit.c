#include <jit.h>

int main(int argc, char const *argv[])
{
    pfile_t *fp = FileIO_New_withMode("../../tests/test.pc", FMODE_READ);
    struct _jit_lexer_ctx_str *ctx = Jit_Lexer_Context_New(FileIO_ReadWholeFile(fp));;

    Jit_Lexer_Initialize(ctx);

    for (size_t i = 0; i < ctx->tok_count; i++)
    {
        Debug_PrintJITToken(stdout, (void *)&ctx->toks[i]);
    }

    FileIO_Close(fp);
    return printf("Program Ended.") && 0;
}
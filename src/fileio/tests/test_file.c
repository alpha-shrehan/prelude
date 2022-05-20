#include <file.h>

int main(int argc, char const *argv[])
{
    pfile_t *f = FileIO_New_withMode("Makefile",
                                     FMODE_READ);
    
    printf("%s\n", FileIO_ReadWholeFile(f));

    FileIO_Close(f);
    return 0;
}
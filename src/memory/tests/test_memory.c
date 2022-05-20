#include <pmemory.h>

int main(int argc, char const *argv[])
{
    char *t = PMemory_Malloc(20 * sizeof(char));
    strcpy(t, "Hello, World!");
    printf("%s\n", t);

    PMemory_Free(t);

    return 0;
}
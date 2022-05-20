#include <prthread.h>

int func(void *arg)
{
    printf("Code: %d\n", *(int *)arg);
    return -1;
}

int main(int argc, char const *argv[])
{
    prthread_t *nt[3];

    for (size_t i = 0; i < 3; i++)
    {
        nt[i] = PRThread_New(&i, (LPTHREAD_START_ROUTINE)func);
        START_THREAD(nt[i]);
    }

    system("pause");

    return 0;
}

#include <utils.h>

int main(int argc, char const *argv[])
{
    char *test[10] = {"hi", "hey", "hello", NULL};
    printf("%d\n", Ut_String_In_StringArray(test, "hi"));
    printf("%d\n", Ut_String_In_StringArray(test, "hey"));
    printf("%d\n", Ut_String_In_StringArray(test, "hello"));
    printf("%d\n", Ut_String_In_StringArray(test, "bye"));
    return 0;
}
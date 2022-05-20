include "main.prh"

strlen(str : char[]) -> int {
    res: int = 0;
    loop {
        if (str[0] == '\0')
            break;
        res++;
    }
    return res;
}
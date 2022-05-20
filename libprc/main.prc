include "main.prh"

decl exit(_Code: int) -> int {
    __sys_exit(_Code);
    return -1;
}
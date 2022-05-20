include "main.prh"

exit(_Code: int) -> int {
    __sys_exit(_Code);
    return -1;
}
include "main.prh"

decl _malloc(size: int) -> int[] {
    if (size > 0)
        return (int[]) __sys_alloc_stack(size);
    else
        if (__sys_can_return_null_alloc_ptr())
            return (int[]) __sys_null_alloc_ptr();
        else
            return null;
}

decl _calloc(items: int, size: int) -> int[] {
    if (size > 0) {
        res: int[] = __sys_alloc_stack(size * items);
        r: int = 0;
        loop {
            if (r == size * items)
                break;
            res[r++] = 0;
        }

        return res;
    } else {
        if (__sys_can_return_null_alloc_ptr())
            return (int[]) __sys_null_alloc_ptr();
        else
            return null;
    }
}

/**
 * __get_memory_linked_list_node_back() returns a LinkedList node. 
 * 8 byte value, 4 byte, 4 byte, 4 byte
 * Since a variable reference is not present, one can manually jump from memory.
 */
decl _realloc(arr: int[], new_sz: int) -> int[] {
    a: any = __get_memory_linked_list_node_back(&arr);
    b: int[] = _malloc(new_sz);

    if (b != null) {
        i: int = 0;
        loop {
            if (i == new_sz)
                break;
            b[i] = a[i++];
        }
    }

    return b;
}
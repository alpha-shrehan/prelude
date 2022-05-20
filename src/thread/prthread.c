#include "prthread.h"

PRTHREAD_API prthread_t *
PRThread_New(
#if defined(_WIN32)
    LPVOID param,
    LPTHREAD_START_ROUTINE f_ptr
#else
    void *param,
    void *(*f_ptr)(void *)
#endif
)
{
    prthread_t *nt = MALLOC(sizeof(prthread_t));
    nt->f_ptr = f_ptr;
    nt->param = param;

#if defined(_WIN32)
    nt->stock = CreateThread(
        0, 0,
        nt->f_ptr,
        nt->param,
        CREATE_SUSPENDED,
        &nt->id);
#else
    // TODO
#endif

    return nt;
}

PRTHREAD_API void
PRThread_Start(prthread_t *_Th)
{
#if defined(_WIN32)
    ResumeThread(_Th->stock);
#else

#endif
}

PRTHREAD_API void
PRThread_Wait(prthread_t *_Th)
{
#if defined(_WIN32)
    WaitForSingleObject(_Th->stock, INFINITE);
#else

#endif
}

PRTHREAD_API void 
PRThread_Wait_withMS(prthread_t *_Th, size_t _Time)
{
#if defined(_WIN32)
    WaitForSingleObject(_Th->stock, _Time);
#else

#endif
}

PRTHREAD_API
#if defined(_WIN32)
DWORD
#else
int
#endif
PRThread_Return(prthread_t *_Th)
{
#if defined(_WIN32)
    GetExitCodeThread(_Th->stock, &_Th->_ret);
#else

#endif
    return _Th->_ret;
}

PRTHREAD_API void 
PRThread_Close(prthread_t *_Th)
{
#if defined(_WIN32)
    CloseHandle(_Th->stock);
#else
    
#endif
}
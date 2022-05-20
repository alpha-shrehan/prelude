#pragma once

#include "Header.h"

#include "../memory/pmemory.h"

struct _prthread_str
{
#if defined(_WIN32)
    HANDLE stock;
    LPVOID param;
    LPTHREAD_START_ROUTINE f_ptr;
    DWORD id;
    DWORD _ret;
#else
    pthread_t *stock;
    void *param;
    void *(*f_ptr)(void *);
    int _ret;
#endif
};

typedef struct _prthread_str prthread_t;

#define START_THREAD(X) PRThread_Start(X)
#define WAIT_THREAD(X, ms) PRThread_Wait_withMS(X, ms)
#define WAIT_THREAD_INFINITE(X) PRThread_Wait(X)

#if defined(__cplusplus)
extern "C"
{
#endif

    /**
     * @brief Create a new thread structure.
     * * IN WINDOWS: THIS DOES NOT INITIALISE THE THREAD.
     * * Manually do it with START_THREAD();
     * * For other operating systems, START_THREAD() does not do anything (neither does PRThread_Start).
     * @return PRTHREAD_API*
     */
    PRTHREAD_API prthread_t *PRThread_New(
#if defined(_WIN32)
        LPVOID param,
        LPTHREAD_START_ROUTINE f_ptr
#else
    void *param,
    void *(*f_ptr)(void *)
#endif
    );

    /**
     * @brief Start a thread.
     * @param _Th Thread object
     * @return PRTHREAD_API
     */
    PRTHREAD_API void PRThread_Start(prthread_t *);

    /**
     * @brief Wait for thread.
     * @param _Th Thread object
     * @return PRTHREAD_API
     */
    PRTHREAD_API void PRThread_Wait(prthread_t *);

    /**
     * @brief Wait for x milliseconds for a thread.
     * @param _Th Thread object
     * @param _Time time in milliseconds
     * @return PRTHREAD_API
     */
    PRTHREAD_API void PRThread_Wait_withMS(prthread_t *, size_t);

    /**
     * @brief Get return code of thread.
     * * Use it after thread is over.
     * @param _Th Thread
     */
    PRTHREAD_API
#if defined(_WIN32)
    DWORD
#else
    int
#endif
    PRThread_Return(prthread_t *);

    /**
     * @brief Close a thread.
     * @param _Th Thread object
     * @return PRTHREAD_API
     */
    PRTHREAD_API void PRThread_Close(prthread_t *);

#if defined(__cplusplus)
}
#endif

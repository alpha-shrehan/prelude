#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>
#include <stdbool.h>
#include <ctype.h>

#if defined(_WIN32)
#   include <Windows.h>
#endif

#include "../memory/pmemory.h"
#include "../fileio/file.h"
#include "../thread/prthread.h"
#include "../utils/utils.h"
#include "../emitter/emit.h"

#if defined(SHARED_BUILD)
#   if defined(_WIN32)
#       if defined(BUILD_EXPORTS)
#           define JIT_API __declspec(dllexport)
#       else
#           define JIT_API __declspec(dllimport)
#       endif
#   else
#       define JIT_API
#   endif
#else
#   define JIT_API
#endif


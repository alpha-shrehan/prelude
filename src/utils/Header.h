#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>
#include <stdbool.h>

#if defined(_WIN32)
#   include <Windows.h>
#endif

#include "../memory/pmemory.h"
#include "../fileio/file.h"
#include "../thread/prthread.h"

#if defined(SHARED_BUILD)
#   if defined(_WIN32)
#       if defined(BUILD_EXPORTS)
#           define UTILS_API __declspec(dllexport)
#       else
#           define UTILS_API __declspec(dllimport)
#       endif
#   else
#       define UTILS_API
#   endif
#else
#   define UTILS_API
#endif


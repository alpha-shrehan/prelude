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

#if defined(SHARED_BUILD)
#   if defined(_WIN32)
#       if defined(BUILD_EXPORTS)
#           define PRC_API __declspec(dllexport)
#       else
#           define PRC_API __declspec(dllimport)
#       endif
#   else
#       define PRC_API
#   endif
#else
#   define PRC_API
#endif

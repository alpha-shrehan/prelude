cmake_minimum_required(VERSION 3.0.0)
project(pcmemory VERSION 0.1.0)

include(CTest)
enable_testing()

add_subdirectory(tests)

add_definitions(-DSHARED_BUILD -DBUILD_EXPORTS)

add_library(pcmemory SHARED
    Header.h
    pmemory.c pmemory.h)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

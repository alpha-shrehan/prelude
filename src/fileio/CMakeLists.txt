cmake_minimum_required(VERSION 3.0.0)
project(pcfileio VERSION 0.1.0)

include(CTest)
enable_testing()

add_subdirectory(tests)

add_definitions(-DSHARED_BUILD -DBUILD_EXPORTS)

add_library(pcfileio SHARED
    Header.h
    file.c file.h)

target_link_libraries(pcfileio
    -L${CMAKE_SOURCE_DIR}/../memory/build -lpcmemory)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_custom_command(
    TARGET pcfileio
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/../memory/build/libpcmemory.dll ${CMAKE_BINARY_DIR}/tests/libpcmemory.dll
)

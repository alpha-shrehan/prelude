cmake_minimum_required(VERSION 3.0.0)
project(pcthread VERSION 0.1.0)

include(CTest)
enable_testing()

add_definitions(-DSHARED_BUILD -DBUILD_EXPORTS)

add_subdirectory(tests)

add_library(pcthread SHARED 
Header.h
prthread.c prthread.h
)

target_link_libraries(pcthread
    -L${CMAKE_SOURCE_DIR}/../memory/build -lpcmemory)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_custom_command(
    TARGET pcthread
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/../memory/build/libpcmemory.dll ${CMAKE_BINARY_DIR}/tests/libpcmemory.dll
)

cmake_minimum_required(VERSION 3.0.0)
project(pcemitter VERSION 0.1.0)

include(CTest)
enable_testing()

add_definitions(-DSHARED_BUILD 
                -DBUILD_EXPORTS
                -DMODE_DEBUG)

add_subdirectory(tests)

add_library(pcemitter SHARED
    Header.h
    structs.c structs.h
    instruction.c instruction.h
    emit.c emit.h
)

target_link_libraries(pcemitter
    -L${CMAKE_SOURCE_DIR}/../memory/build -lpcmemory)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_custom_command(
    TARGET pcemitter
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/../memory/build/libpcmemory.dll ${CMAKE_BINARY_DIR}/libpcmemory.dll)
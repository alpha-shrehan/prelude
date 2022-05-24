cmake_minimum_required(VERSION 3.0.0)
project(pcjit VERSION 0.1.0)

include(CTest)
enable_testing()

add_definitions(-DSHARED_BUILD 
                -DBUILD_EXPORTS
                -DMODE_DEBUG)

add_subdirectory(tests)

add_library(pcjit SHARED
    Header.h jit.h
    structs.c structs.h
    debug.c debug.h
    ast.c ast.h
    parser.c parser.h)

target_link_libraries(pcjit
    -L${CMAKE_SOURCE_DIR}/../memory/build -lpcmemory
    -L${CMAKE_SOURCE_DIR}/../thread/build -lpcthread
    -L${CMAKE_SOURCE_DIR}/../utils/build -lpcutils
    -L${CMAKE_SOURCE_DIR}/../fileio/build -lpcfileio
    -L${CMAKE_SOURCE_DIR}/../emitter/build -lpcemitter)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_custom_command(
    TARGET pcjit
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/../memory/build/libpcmemory.dll ${CMAKE_BINARY_DIR}/libpcmemory.dll && ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/../thread/build/libpcthread.dll ${CMAKE_BINARY_DIR}/libpcthread.dll && ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/../utils/build/libpcutils.dll ${CMAKE_BINARY_DIR}/libpcutils.dll && ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/../fileio/build/libpcfileio.dll ${CMAKE_BINARY_DIR}/libpcfileio.dll && ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/../emitter/build/libpcemitter.dll ${CMAKE_BINARY_DIR}/libpcemitter.dll)

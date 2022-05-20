include_directories(../)
add_executable(test_jit_exe test_jit.c)
target_link_libraries(test_jit_exe pcjit)
add_test(test_jit test_jit_exe)

add_custom_command(
    TARGET test_jit_exe
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/libpcfileio.dll ${CMAKE_BINARY_DIR}/tests/libpcfileio.dll && ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/libpcjit.dll ${CMAKE_BINARY_DIR}/tests/libpcjit.dll && ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/libpcmemory.dll ${CMAKE_BINARY_DIR}/tests/libpcmemory.dll && ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/libpcthread.dll ${CMAKE_BINARY_DIR}/tests/libpcthread.dll && ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/libpcutils.dll ${CMAKE_BINARY_DIR}/tests/libpcutils.dll)
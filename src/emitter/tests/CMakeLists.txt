include_directories(../)
add_executable(test_emitter_exe test_emitter.c)
target_link_libraries(test_emitter_exe pcemitter)
add_test(test_emit test_emitter_exe)

add_custom_command(
    TARGET test_emitter_exe
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/libpcemitter.dll ${CMAKE_BINARY_DIR}/tests/libpcemitter.dll && ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/libpcmemory.dll ${CMAKE_BINARY_DIR}/tests/libpcmemory.dll)
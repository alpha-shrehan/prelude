include_directories(../)

add_executable(test_memory_exe test_memory.c)
target_link_libraries(test_memory_exe pcmemory)
add_test(test_memory test_memory_exe)

add_custom_command(TARGET test_memory_exe POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/libpcmemory.dll ${CMAKE_BINARY_DIR}/tests/libpcmemory.dll
)
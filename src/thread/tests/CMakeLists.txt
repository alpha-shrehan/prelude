include_directories(../)
add_executable(test_thread_exe test_thread.c)
target_link_libraries(test_thread_exe pcthread)
add_test(test_thread test_thread_exe)

add_custom_command(TARGET test_thread_exe POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/libpcthread.dll ${CMAKE_BINARY_DIR}/tests/libpcthread.dll)
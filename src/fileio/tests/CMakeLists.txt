include_directories(../)

add_executable(test_file_exe test_file.c)
target_link_libraries(test_file_exe pcfileio)
add_test(test_file test_file_exe)

add_custom_command(
    TARGET test_file_exe
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/libpcfileio.dll ${CMAKE_BINARY_DIR}/tests/libpcfileio.dll
)
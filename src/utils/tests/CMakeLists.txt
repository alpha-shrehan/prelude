include_directories(../)

add_executable(string_utils_test_exe string_utils_test.c)
target_link_libraries(string_utils_test_exe pcutils)
add_test(string_utils_test string_utils_test_exe)

add_custom_command(TARGET string_utils_test_exe POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/libpcutils.dll ${CMAKE_BINARY_DIR}/tests/libpcutils.dll
)
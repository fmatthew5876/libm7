
add_executable(vec vec.C)
target_link_libraries(vec gtest_main m7)

add_executable(matrix matrix.C)
target_link_libraries(matrix gtest_main m7)

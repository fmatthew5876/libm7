
add_executable(vec vec.C)
target_link_libraries(vec gtest_main m7)

add_executable(mat mat.C)
target_link_libraries(mat gtest_main m7)

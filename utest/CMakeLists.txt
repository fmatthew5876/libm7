link_libraries(gtest)

add_executable(type_traits type_traits.C)
target_link_libraries(type_traits gtest_main)

add_executable(string_table type_traits.C)
target_link_libraries(string_table gtest_main m7)

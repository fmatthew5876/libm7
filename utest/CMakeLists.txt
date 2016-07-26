link_libraries(gtest)

add_executable(type_traits type_traits.C)
target_link_libraries(type_traits gtest_main)

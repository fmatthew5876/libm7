link_libraries(gtest)

#add_executable(type_traits type_traits.C)
#target_link_libraries(type_traits gtest_main)

#add_executable(string_table string_table.C)
#target_link_libraries(string_table gtest_main m7)

add_executable(PagedPoolAllocator PagedPoolAllocator.C)
target_link_libraries(PagedPoolAllocator gtest_main m7)

add_subdirectory(m)

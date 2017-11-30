link_libraries(gtest)

#add_executable(type_traits type_traits.C)
#target_link_libraries(type_traits gtest_main)

add_executable(bitops bitops.C)
target_link_libraries(bitops gtest_main m7)

add_executable(ascii ascii.C)
target_link_libraries(ascii gtest_main m7)

add_executable(ArrayView ArrayView.C)
target_link_libraries(ArrayView gtest_main m7)

add_executable(StringTable StringTable.C)
target_link_libraries(StringTable gtest_main m7)

add_executable(WindowBuffer WindowBuffer.C)
target_link_libraries(WindowBuffer gtest_main m7)

add_executable(PagedPoolAllocator PagedPoolAllocator.C)
target_link_libraries(PagedPoolAllocator gtest_main m7)

add_executable(FrameAllocator FrameAllocator.C)
target_link_libraries(FrameAllocator gtest_main m7)

add_subdirectory(m)

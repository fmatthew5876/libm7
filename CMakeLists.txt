cmake_minimum_required(VERSION 3.5.1)
project(libm7)

configure_file(
	"${PROJECT_SOURCE_DIR}/include/m7/config.H.in"
	"${PROJECT_BINARY_DIR}/include/m7/config.H"
	)
include_directories(BEFORE "${PROJECT_BINARY_DIR}/include ${PROJECT_SOURCE_DIR}/include")

include_directories(./include)
add_compile_options(-std=c++14 -Wall -Wextra)

set(CMAKE_CXX_FLAGS_DEBUG "-g -Og")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g -O2")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

install(DIRECTORY include DESTINATION .
	FILES_MATCHING
	PATTERN "*.H"
	PATTERN "iterator"
	)

add_subdirectory(ext)

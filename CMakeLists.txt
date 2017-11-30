cmake_minimum_required(VERSION 3.5.1)
cmake_policy(SET CMP0048 NEW)

project(libm7 VERSION 0.0.0.0)

include(CheckFunctionExists)
check_function_exists(sincos M7_HAVE_SINCOS_FUNCTION)

configure_file(
	"${PROJECT_SOURCE_DIR}/libm7.pc.in"
	"${PROJECT_BINARY_DIR}/libm7.pc"
	)

configure_file(
	"${PROJECT_SOURCE_DIR}/include/m7/config.H.in"
	"${PROJECT_BINARY_DIR}/include/m7/config.H"
	)
include_directories(BEFORE ${PROJECT_BINARY_DIR}/include ${PROJECT_SOURCE_DIR}/include)

#Create compile commands file and copy to root.
SET( CMAKE_EXPORT_COMPILE_COMMANDS ON)
IF( EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json" )
  EXECUTE_PROCESS( COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
    ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
  )
ENDIF()

include_directories(./include)
add_compile_options(-std=c++1z -Wall -Wextra)

set(CMAKE_CXX_FLAGS_DEBUG "-g -Og")
set(CMAKE_CPP_FLAGS_DEBUG "-DM7_DEBUG")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g -O2")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

install(DIRECTORY include DESTINATION .
	FILES_MATCHING
	PATTERN "*.H"
	)

add_subdirectory(ext)
add_subdirectory(utest)
add_subdirectory(src)
add_subdirectory(doc)

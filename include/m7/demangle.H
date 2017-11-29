#pragma once
#include <string_view>

namespace m7 {

///Demangles the given C++ symbol name.
///The returned char* pointer refers to an internally managed
///thread_local buffer. Everytime this function is called
///the pointers returned by previous calls are invalidated.
///You must make a copy of the string if you want to keep it around
///long term.
const char* demangle(const char* name);

}

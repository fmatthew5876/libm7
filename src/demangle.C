#include <m7/demangle.H>
#include <cstdlib>

#ifdef __GNUC__
#include <cxxabi.h>

namespace m7 {

namespace {

struct MangleBuf {
    char* buf = nullptr;
    size_t len = 0;

    ~MangleBuf() {
        std::free(buf);
    }
};

static thread_local MangleBuf tls_mangle;

} //namespace

const char* demangle(const char* mangled_name) {
    int status = 0;

    auto* p = ::abi::__cxa_demangle(mangled_name, tls_mangle.buf, &tls_mangle.len, &status);
    if(p == nullptr) {
        return mangled_name;
    }
    tls_mangle.buf = p;
    return p;
}

} //namespace m7

#else

namespace m7 {

const char* demangle(const char* name) {
    return name;
}

} //namespace m7

#endif


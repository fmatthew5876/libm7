#pragma once
#include <m7/ExceptionDef.H>

namespace m7 {

inline Exception::Exception() {
    if(default_do_stack_trace()) {
        append_stack_trace();
    }
}

inline Exception::Exception(ExceptionDumpStack flag) {
    if(flag == ExceptionDumpStack::eYes) {
        append_stack_trace();
    }
}

inline Exception::Exception(std::string msg)
    : _msg(std::move(msg))
{
    if(default_do_stack_trace()) {
        append_stack_trace();
    }
}

inline Exception::Exception(std::string msg, ExceptionDumpStack flag)
    : _msg(std::move(msg))
{
    if(flag == ExceptionDumpStack::eYes) {
        append_stack_trace();
    }
}

inline const char* Exception::what() const noexcept {
    return _msg.c_str();
}

inline bool Exception::default_do_stack_trace() {
    return _default_do_stack_trace.load();
}

inline void Exception::default_do_stack_trace(bool val) {
    return _default_do_stack_trace.store(val);
}


}  // namespace m7

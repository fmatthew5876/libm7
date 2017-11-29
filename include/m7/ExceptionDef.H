#pragma once
#include <m7/ExceptionFwd.H>
#include <atomic>
#include <exception>
#include <string>

namespace m7 {

enum class ExceptionDumpStack {
    eNo,
    eYes
};

/// Base class for all libm7 exceptions.
class Exception : public std::exception {
    public:
        /// Construct with empty message and defaulted stack tracing.
        Exception();

        /// Construct with empty message and configured stack tracing.
        explicit Exception(ExceptionDumpStack flag);

        /// Construct with given message and defaulted stack tracing.
        explicit Exception(std::string msg);

        /// Construct with given message and configured stack tracing.
        Exception(std::string msg, ExceptionDumpStack flag);

        /// Return embedded message.
        virtual const char* what() const noexcept override;

        /// true if by default we enable stack traces on exception.
        static bool default_do_stack_trace();

        /// set whether if by default we enable stack traces on exception.
        static void default_do_stack_trace(bool val);

    protected:
        /// Append a stack trace to the stored message.
        void append_stack_trace();

    protected:
        /// The underlying message returned by what()
        std::string _msg;

    private:
        static std::atomic<bool> _default_do_stack_trace;
};

}

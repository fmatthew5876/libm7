#include <m7/Exception.H>
#include <m7/demangle.H>
#include <sstream>
#include <iomanip>

#define UNW_LOCAL_ONLY
#include <libunwind.h>

namespace m7 {

static constexpr size_t kMaxBufLen = 4096;

std::atomic<bool> Exception::_default_do_stack_trace(true);


void Exception::append_stack_trace() {
    unw_cursor_t cursor;
    unw_context_t uc;
    unw_proc_info_t pip;
    unw_word_t ip;
    unw_word_t sp;
    unw_word_t offp;
    int rc = 0;

    char buf[kMaxBufLen];
    int frame = 0;

    //FIXME: Use fmtlib here!
    std::ostringstream ss;

    ss << "\n\nStack Trace:\n";

    rc = unw_getcontext(&uc);
    if(rc != 0) {
        ss << "\tError: unw_getcontext() failed : " << unw_strerror(rc) << '\n';
        goto egress;
    }
    rc = unw_init_local(&cursor, &uc);
    if(rc != 0) {
        ss << "\tError: unw_init_local() failed : " << unw_strerror(rc) << '\n';
        goto egress;
    }

    for(;;++frame) {
        rc = unw_step(&cursor);
        if(rc < 0) {
            ss << "\tError: unw_step() failed : " << unw_strerror(rc) << '\n';
            goto egress;
        }
        if(rc == 0) {
            break;
        }

        ss << '\t' << std::dec << frame << ": " << std::hex;

        rc = unw_get_proc_name(&cursor, buf, sizeof(buf), &offp);
        if(rc == 0 || rc == UNW_ENOMEM) {
            ss << demangle(buf) << " off=0x" << (long)offp;
        } else {
            ss << " ???? (" << unw_strerror(rc) << ")";
        }

        rc = unw_get_reg(&cursor, UNW_REG_IP, &ip);
        if(rc == 0) {
            ss << " ip=0x" << (long)ip;
        } else {
            ss << " ip=????";
        }

        rc = unw_get_reg(&cursor, UNW_REG_SP, &sp);
        if(rc == 0) {
            ss << " sp=0x" << (long)sp;
        } else {
            ss << " sp=????";
        }

        rc = unw_get_proc_info(&cursor, &pip);
        if(rc == 0) {
            ss << " start_ip=0x" << long(pip.start_ip) << " end_ip=0x" << long(pip.end_ip) << " handler=0x" << long(pip.handler) << std::endl;
        } else {
            ss << " start_ip=???? end_ip=???? handler=????";
        }

        ss << '\n';
    }

egress:
    _msg += ss.str();
    return;
}

} //namespace m7

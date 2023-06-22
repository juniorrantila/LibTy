#pragma once
#include <Ty/Arch.h>

namespace Async {

#if ARCH(x86_64) && (OS(darwin) || OS(linux))

struct Context {
    void* rip;
    void* rsp;
    void* rbx;
    void* rbp;
    void* r12;
    void* r13;
    void* r14;
    void* r15;
};

#else
#error "Unsupported architecture or OS"
#endif

}

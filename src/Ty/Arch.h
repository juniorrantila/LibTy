#pragma once

#if defined(_WIN32)
#define __TY_OS_windows 1
#elif defined(__APPLE__)
#define __TY_OS_darwin 1
#elif defined(__linux__)
#define __TY_OS_linux 1
#else
#error "Unknown OS"
#endif
#define OS(query) __TY_OS_##query


#if defined(__x86_64__)
#define __TY_ARCH_x86_64 1
#else
#error "Unknown cpu family"
#endif
#define ARCH(query) __TY_ARCH_##query

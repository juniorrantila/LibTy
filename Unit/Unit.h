#pragma once
#include "Expect.h"

#ifdef LIBTY_INCLUDE_TESTS
#    include "TestCase.h"

#    define TEST_CASE(__name)                              \
        static char const* __name##_test_func();           \
        static auto __name##_test_init                     \
            = Unit::TestCase(#__name, __name##_test_func); \
        static char const* __name##_test_func()

#else

#    define TEST_CASE(__name) \
        [[maybe_unused]] static char const* __name##_test_func()

#endif

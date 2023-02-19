#pragma once
#include "TestContext.h"

namespace Unit {

using RunFunction = char const* (*)();
struct TestCase {
    char const* m_name { nullptr };
    RunFunction m_run { nullptr };

    // NOTE: noexcept to silence warning for static init.
    TestCase(char const* name, RunFunction run) noexcept;

    char const* name() const { return m_name; }
    char const* run() const { return m_run(); }

    static void run_all(TestContext);
    static void append(TestCase);

    static constexpr auto s_max_tests = 1024;
    static unsigned int s_tests_size;
    static TestCase s_tests[s_max_tests];

private:
    constexpr TestCase() = default;
};

}

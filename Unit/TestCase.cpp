#include "TestCase.h"
#include <stdio.h>

namespace Unit {

unsigned int TestCase::s_tests_size = 0;
TestCase TestCase::s_tests[TestCase::s_max_tests];

TestCase::TestCase(char const* name, RunFunction run) noexcept
    : m_name(name)
    , m_run(run)
{
    TestCase::append(*this);
}

void TestCase::append(TestCase test)
{
    if (s_tests_size == s_max_tests)
        __builtin_trap();
    s_tests[s_tests_size++] = test;
}

void TestCase::run_all(TestContext context)
{
    printf("got to here!");
    context.notify_init(s_tests_size);
    for (unsigned int id = 0; id < s_tests_size; id++) {
        auto test = s_tests[id];
        context.notify_test_started(id, test.name());
        context.notify_test_finished(id, test.run());
    }
    context.notify_deinit();
}

}

#include "RunAllTests.h"

// NOTE: Defining this elsewhere removes the symbol :(
void unit_run_all_tests(Unit::TestContext context)
{
    Unit::TestCase::run_all(context);
}

#include "TestContext.h"

namespace Unit {

void TestContext::notify_startup_failed(char const* message) const
{
    if (on_startup_failed)
        on_startup_failed(user_context, message);
}

void TestContext::notify_init(unsigned int number_of_tests) const
{
    if (on_init)
        on_init(user_context, number_of_tests);
}

void TestContext::notify_deinit() const
{
    if (on_deinit)
        on_deinit(user_context);
}

void TestContext::notify_test_started(unsigned int id,
    char const* name) const
{
    if (on_test_started)
        on_test_started(user_context, id, name);
}

void TestContext::notify_test_finished(unsigned int id,
    char const* message) const
{
    if (on_test_finished)
        on_test_finished(user_context, id, message);
}

}

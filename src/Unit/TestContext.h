#pragma once
#include "Forward.h"

namespace Unit {

struct TestContext {
    friend TestCase;
    friend TestSuite;
    void* user_context { 0 };

    void (*on_startup_failed)(void* user_ctx,
        char const* message) { 0 };
    void (*on_init)(void* user_ctx,
        unsigned int number_of_tests) { 0 };
    void (*on_deinit)(void* user_ctx) { 0 };

    void (*on_test_started)(void* user_ctx, unsigned int id,
        char const* name) { 0 };
    void (*on_test_finished)(void* user_ctx, unsigned int id,
        char const* message) { 0 };

private:
    void notify_startup_failed(char const* message) const;
    void notify_init(unsigned int number_of_tests) const;
    void notify_deinit() const;
    void notify_test_started(unsigned int id,
        char const* name) const;
    void notify_test_finished(unsigned int id,
        char const* message) const;
};

}

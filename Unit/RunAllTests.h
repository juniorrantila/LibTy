#pragma once
#include "Forward.h"

#define UNIT_TEST_RUNNER_NAME "unit_run_all_tests"
extern "C" {

extern void unit_run_all_tests(Unit::TestContext) asm(
    UNIT_TEST_RUNNER_NAME);
}

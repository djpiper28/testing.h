#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "logger.h"
#include "ansi_colour.h"

#define TESTS_SIZE(tests) (sizeof(tests) / sizeof(*tests))
#define SUB_TEST(test_name, ...) \
int test_name() \
{ \
  unit_test tests[] = { \
    __VA_ARGS__, \
  }; \
  \
  int failed_tests = run_tests(tests, TESTS_SIZE(tests), "Running Sub Module " #test_name " Tests"); \
  lprintf(LOG_INFO, "%d/%d tests failed.\n", failed_tests, TESTS_SIZE(tests)); \
  return failed_tests == 0; \
}

#define TEST_FAIL ANSI_RED    "test-fail" ANSI_RESET
#define TEST_PASS ANSI_GREEN  "test-pass" ANSI_RESET
#define TEST_INFO ANSI_YELLOW "test-info" ANSI_RESET
#define ASSERT(x) if (!(x)) \
{ \
  lprintf(LOG_ERROR, "Test Error: Assertion failure, line " \
      ANSI_RED "%d" ANSI_RESET " in " ANSI_RED "%s" ANSI_RESET "\n", \
      __LINE__, __FILE__); return 0; \
}

typedef struct unit_test {
    int (*test_method)();
    const char *test_name;
} unit_test;

// Standalone test for a function
int test_func(int (*test_method)(), const char *test_name);
// Test a set if named functions
int run_tests(unit_test *tests, size_t number, const char *module_name);

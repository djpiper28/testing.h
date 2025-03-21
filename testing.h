#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "logger.h"
#include "ansi_colour.h"

#ifdef __cplusplus
extern "C" {
#endif

/// ARRAY_SIZE wrapper
#define TESTS_SIZE(tests) (sizeof(tests) / sizeof(*tests))
/// Creates a method to run a list of sub tests
/// Usage: SUB_TEST(method_name, {&method_1, "Description"}, ...)
#define SUB_TEST(test_name, ...) \
int test_name() \
{ \
  unit_test tests[] = { \
    __VA_ARGS__, \
  }; \
  \
  int failed_tests = run_tests(tests, TESTS_SIZE(tests), "Running Sub Module " ANSI_GREEN #test_name ANSI_RESET " Tests"); \
  lprintf(LOG_INFO, "%ld/%ld tests failed.\n", failed_tests, TESTS_SIZE(tests)); \
  return failed_tests == 0; \
}

/// Creates a method to run all of the tests, it takes the same arguments 
/// as masin(): `(int argc, char **argv)`. It then parses these arguments
/// to allow limited amounts of tests to be executed
/// Usage: MAIN_TEST(method_name, {&method_1, "Description"}, ...)
#define MAIN_TEST(test_name, ...) \
int test_name(int argc, char **argv) \
{ \
  unit_test tests[] = { \
    __VA_ARGS__, \
  }; \
  \
  int failed_tests = run_main_tests(argc, argv, tests, TESTS_SIZE(tests), "Running tests for" ANSI_GREEN #test_name ANSI_RESET " Tests"); \
  lprintf(LOG_INFO, "%ld/%ld tests failed.\n", failed_tests, argc - 1); \
  return failed_tests == 0; \
}

#define TEST_FAIL ANSI_RED    "test-fail" ANSI_RESET
#define TEST_PASS ANSI_GREEN  "test-pass" ANSI_RESET
#define TEST_INFO ANSI_YELLOW "test-info" ANSI_RESET

/// ASSERT(condition) if the condition is true then nothing happens
/// otherwise this will print an error and return 0 
#define ASSERT(x) if (!(x)) \
{ \
  lprintf(LOG_ERROR, "Test Error: Assertion failure, line " \
      ANSI_RED "%d" ANSI_RESET " in " ANSI_RED "%s" ANSI_RESET "\n", \
      __LINE__, ___FNANE); return 0; \
}

typedef struct unit_test {
    int (*test_method)();
    const char *test_name;
} unit_test;

/// Standalone test for a function
int test_func(int (*test_method)(), const char *test_name);
/// Test a set of named functions
int run_tests(unit_test *tests, size_t number, const char *module_name);
/// Test some or all of the functions based off of the user input in argc, and argv
int run_main_tests(int argc, char **argv, unit_test *tests, size_t number, const char *module_name);

#ifdef __cplusplus
}
#endif


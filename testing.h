#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "ansi_colour.h"

#define ASSERT(x) if (!(x)) { printf(ANSI_BACKGROUND_RED "Test Error: Assertion failure, line %d in %s" ANSI_RESET "\n", __LINE__, __FILE__); return 0; }

typedef struct unit_test {
    int (*test_method)();
    const char *test_name;
} unit_test;

// Standalone test for a function
int test_func(int (*test_method)(), const char *test_name);
// Test a set if named functions
int run_tests(unit_test *tests, size_t number, const char *module_name);

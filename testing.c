#include "testing.h"

int test_func(int (*test_method)(), const char *test_name)
{
    lprintf(TEST_INFO, "Running unit test " ANSI_GREEN "%s" ANSI_RESET ": \n", test_name);

    int status = test_method();
    if (status) {
        lprintf(TEST_PASS, "Unit test " ANSI_YELLOW "%s" ANSI_RESET " passed\n", test_name);
    } else {
        lprintf(TEST_FAIL, "Unit test " ANSI_YELLOW "%s" ANSI_RESET " failed\n", test_name);
    }

    return status;
}

int run_tests(unit_test *tests, size_t number, const char *module_name)
{
    size_t failed = 0;
    lprintf(TEST_INFO, "Running %ld tests for %s\n", number, module_name);
    for (size_t i = 0; i < number; i++) {
        unit_test test = tests[i];
        int status = test_func(test.test_method, test.test_name);

        if (!status) {
            failed++;
        }
    }

    lprintf(TEST_INFO, "%ld/%ld tests passed for %s\n", (number - failed), number, module_name);
    if (failed != 0) {
        lprintf(TEST_INFO, "%ld tests failed for %s\n", failed, module_name);
    }

    return failed;
}

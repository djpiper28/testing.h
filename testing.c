#include "testing.h"

int test_func(int (*test_method)(), const char *test_name)
{
    printf(ANSI_YELLOW "Info: Testing %s: " ANSI_RESET "\n", test_name);

    int status = test_method();
    if (status) {
        printf(ANSI_GREEN "Test-Pass: Test %s passed." ANSI_RESET "\n", test_name);
    } else {
        printf(ANSI_RED "Test-Fail: Test %s failed." ANSI_RESET "\n", test_name);
    }

    return status;
}

int run_tests(unit_test *tests, size_t number, const char *module_name)
{
    size_t failed = 0;
    printf(ANSI_YELLOW "Info: Running %ld tests for %s" ANSI_RESET "\n", number, module_name);
    for (size_t i = 0; i < number; i++) {
        unit_test test = tests[i];
        int status = test_func(test.test_method, test.test_name);

        if (!status) {
            failed++;
        }
    }

    printf(ANSI_YELLOW "Info: %ld/%ld tests passed for %s" ANSI_RESET "\n", (number - failed), number, module_name);
    if (failed != 0) {
        printf(ANSI_BACKGROUND_RED "Error: %ld tests failed" ANSI_RESET "\n", failed);
    }

    return failed;
}

#include "testing.h"
#include "logger.h"
#include <string.h>

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

int run_main_tests(int argc, char **argv, unit_test *tests, size_t number, const char *module_name)
{
    if (argc == 1) {
        lprintf(LOG_INFO, "Running all tests, for more info run: '%s help'\n", argv[0]);
        return run_tests(tests, number, module_name);
    }

    if (strcmp(argv[1], "help") == 0) {
        lprintf(LOG_INFO, "Running no tests - displaying help\n");
        printf("Usage: %s (--help ?) TESTS...\n", argv[0]);
        printf("i.e: %s 0 1 3\n", argv[0]);

        printf("TESTS are:\n\tArg | Description\n");
        for (size_t i = 0; i < number; i++) {
            printf("\t% 3ld | %s\n", i, tests[i].test_name);
        }
        exit(EXIT_FAILURE);
    }

    size_t failed = 0;
    lprintf(TEST_INFO, "Running %d/%ld tests for %s\n", argc - 1, number, module_name);

    for (size_t i = 1; i < argc; i++) {
        char *end = NULL;
        long test_num = strtol(argv[i], &end, 10);
        if (argv[i] == end || test_num < 0 || test_num >= number) {
           lprintf(LOG_ERROR, "Invalid argument %s, see valid args with: %s help\n", argv[i], argv[0]);
           exit(EXIT_FAILURE);
        }

        unit_test test = tests[test_num];
        int status = test_func(test.test_method, test.test_name);

        if (!status) {
            failed++;
        }
    }

    lprintf(TEST_INFO, "%d/%ld tests passed for %s\n", (argc - 1 - failed), argc - 1, module_name);
    if (failed != 0) {
        lprintf(TEST_INFO, "%ld tests failed for %s\n", failed, module_name);
    }

    return failed;
}

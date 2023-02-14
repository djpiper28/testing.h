#include "testing.h"

int test_assert()
{
    ASSERT(1 == 1);
    ASSERT(0);
}

int test_fail()
{
    return 0;
}

int test_pass()
{
    return 1;
}

int main()
{
    if (test_func(&test_assert, "test_assert")) {
        printf("Error ASSERT does not fail tests\n");
        exit(1);
    }

    unit_test tests[] = {
        {&test_fail, "This test should fail"},
        {&test_fail, "This test should fail"},
        {&test_pass, "This test should pass"}
    };

    int res = run_tests(tests, sizeof(tests) / sizeof(*tests), "module name");
    if (res != 2) {
        printf("Error run_tests does not run tests and, return the amount of failures\n");
        exit(2);
    }

    printf("The self tests passed\n");
    exit(0);
}

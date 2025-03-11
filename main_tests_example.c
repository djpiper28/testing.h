#include "./testing.h"

static int test_add_nums()
{
    ASSERT(2 + 2 == 4);
    return 1;
}

static int test_sub_nums()
{
    ASSERT(2 - 2 == 0);
    return 1;
}

MAIN_TEST(tests, {&test_add_nums, "Test add nums"},
          {&test_sub_nums, "Test sub nums"})

int main(int argc, char **argv)
{
    return tests(argc, argv) ? 0 : 1;
}

# testing.h
[![C](https://github.com/djpiper28/testing.h/actions/workflows/c.yml/badge.svg)](https://github.com/djpiper28/testing.h/actions/workflows/c.yml)

## Usage
```c
#include "testing.h"

int test_func()
{
	  ASSERT(1 == 1);
	  return 1;
}

//...

unit_test tests[] = {
	  {&test_func, "This test will pass as 1 == 1"}
};
int failed_tests = run_tests(tests, sizeof(tests) / sizeof(*tests), "the module you have just tested");
```

## Using SUB\_TEST to Generate a Test Function To Test a Set of Tests as a Sub Module
```c
SUB_TEST(coins_cpp_test, 
  {&test_coins, "flip coins"}, 
  {&test_krark_coins, "flip krark coins"}
)

// Creates
int coins_cpp_test()
{
  // Runs tests for all the arguments of SUB_TEST
}
```


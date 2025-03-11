all:
	gcc -g testing.c logger.c test.c -o tests
	gcc -g testing.c logger.c main_tests_example.c -o main_test_example

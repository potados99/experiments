#ifndef _tests
#define _tests

#include <stdbool.h>
#include <stddef.h>

typedef bool (*test_function)(void);

#define TEST(_name)											\
	static bool _name(void)								

#define ASSERT(_condition)									\
	do {													\
		if (!_condition) {									\
				puts("Assertion failed: " #_condition);		\
				return false;								\
		} else {											\
				puts("Assertion succeeded: " #_condition);	\
		}													\
	} while (0)												

void run_tests();

extern size_t 			testc;
extern test_function 	testv[];

#endif /* _tests */

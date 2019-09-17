#ifndef _tests
#define _tests

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef bool (*test_function)(void);

#define TEST(_name)												\
	static bool _name(void)								

#define ASSERT(_condition)										\
	do {														\
		if (!(_condition)) {									\
				puts("Assertion failed: " #_condition);			\
				return false;									\
		} else {												\
				puts("Assertion succeeded: " #_condition);		\
		}														\
	} while (0)												

extern size_t 			testc;
extern test_function 	testv[];

static inline void run_tests() {
	for (size_t i = 0; i < testc; ++i) {
		printf("==== Test %zu Started ====\n", i);
		printf("==== Test %zu %s ====\n\n", i, testv[i]() ? "Succeeded" : "Failed");
	}
}

#endif /* _tests */

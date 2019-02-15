
#include "test.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 170

static inline void print_at_position(char symbol, int position) {
	putchar('|');

	for (int i = 0; i < position - 1; ++i) {
		putchar(' ');
	}

	putchar(symbol);

	for (int i = 0; i < SIZE - position; ++i) {
		putchar(' ');
	}

	putchar('|');

	putchar('\n');
}

void rand_test_1() {
	int num = 0;
	int delay = 30000;
	int addition = 0;

	for (int i = 0; i < SIZE; ++i) {
		srand(rand() + i + 5);
		addition = (rand() % 11 + 15);
		delay = (rand() % 10 > 4) ?
		delay + (500 * addition) :
		delay - (500 * addition);
		delay = (delay < 0) ?
		delay * -1 :
		delay;
		delay = (delay > 70000) ?
		delay / 2 :
		delay;

		for (int j = 0; j < SIZE; ++j) {
			srand(rand() + i * j + j);
			num = (rand() % SIZE) + 1;

			print_at_position('*', num);
			USLEEP(delay);
		} /* end of for j */
	} /* end of for i */
}

void rand_test_2() {
	int num;
	int positions[SIZE] = {0, };

	for (int i = 0; i < SIZE; ++i) {
		memset(positions, 0, sizeof(positions));

		for (int j = 0; j < SIZE; ++ j) {
			srand(rand() + i * j + j);
			num = (rand() % SIZE) + 1; /* 1 to 100 */
			positions[num] += 1;
		}

		putchar('|');

		for (int j = 0; j < SIZE - 1; ++j) {
			putchar(positions[j + 1] ? positions[j + 1] + '0' : ' ');
		}

		putchar('|');
		putchar('\n');
		USLEEP(50000);
	}
}

void hash_dist_test() {
	int num = 0;
	int delay = 30000;

	for (int i = 1; i; ++i) {
		num = (hash(i) % SIZE) + 1;
		print_at_position('*', num);
		USLEEP(delay);
	}
}

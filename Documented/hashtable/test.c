
#include "test.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define SIZE 170

static void print_at_position(char symbol, int position) {
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
	int num;
	int delay = 30000;

	for (int i = 0; i < SIZE; ++i) {
		delay = (rand() % 3 - 1) ? delay + 10000 : delay - 10000;
		printf("Change to %d!\n", delay);

		for (int j = 0; j < SIZE; ++j) {
			srand(time(NULL) + i * j + j);
			num = (rand() % SIZE) + 1;
			print_at_position('*', num);
			usleep(delay);
		}
	}
}

void rand_test_2() {
	int num;
	int positions[SIZE] = {0, };

	for (int i = 0; i < SIZE; ++i) {
		memset(positions, 0, sizeof(positions));

		for (int j = 0; j < SIZE; ++ j) {
			srand(time(NULL) + i * j + j);
			num = (rand() % SIZE) + 1; /* 1 to 100 */
			positions[num] += 1;
		}

		putchar('|');

		for (int j = 0; j < SIZE - 1; ++j) {
			putchar(positions[j + 1] ? positions[j + 1] + '0' : ' ');
		}

		putchar('|');
		putchar('\n');
		usleep(50000);
	}
}

void hash_dist_test() {

}

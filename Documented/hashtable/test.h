#ifndef test_h
#define test_h

#include "hash.h"

#define USLEEP(_X)                                                \
do {                                                              \
  struct timespec _req = { .tv_sec = 0, .tv_nsec = (_X) * 1000};  \
  nanosleep(&_req, NULL);                                         \
} while (0)


void rand_test_1(void);
void rand_test_2(void);

void hash_dist_test(void);

#endif /* test_h */

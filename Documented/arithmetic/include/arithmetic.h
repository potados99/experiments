#ifndef _arithmetic
#define _arithmetic

#include <stdbool.h>

/**
  * Check overflow
  */
bool tadd_ok(int x, int y);
bool tsub_ok(int x, int y);
bool tmult_ok(int x, int y);

int div16(int x);

#endif /* _arithmetic */

#include "routines.h"

/**
  * See routines.h and routines.c for more information.
  */
int main(int argc, char *const argv[]) {
	setup();

	while(1) {
		loop();
	}

	return 0;
}

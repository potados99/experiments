#include "launch.h"

#include <stdio.h>

int launch(char *const argv[], int bg) {

	printf("going to launch %s ", argv[0]);
	
	if (argv[1]) printf("with arg: ");
	for (int i = 1; argv[i]; ++i) {
		printf("%s ", argv[i]);
	}

	printf("on %s.\n", (bg ? "background" : "foreground"));

	printf("\n");

	return 0;
}

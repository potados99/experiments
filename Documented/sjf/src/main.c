#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pio.h"

int do_what(const char *content, int len);

int main(int argc, const char * argv[]) {
	if (argc != 2) goto usage; 
	
	p_with_file(argv[1], do_what);

	return 0;


/************** Wrong arguments ***************/
usage:
	puts("Usage:");
	puts("sjf [process data file]");

	return -1;
/**********************************************/
}

int do_what(const char *content, int len) {

	printf("read: %d bytes, content: \n[%s]\n", len, content);

	return 0;

}

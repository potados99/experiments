#include <stdio.h>
#include <stdlib.h>
#include <string.h>


const char *constant_str() {
	return "I am a string literal in form of const char *!\n";
}

char *str() {
	return "I am a string literal!\n";
}

int main(int argc, const char * argv[]) {
	
	printf("result of [const char *constant_str()]: %s", constant_str());
	printf("result of [char *str()]: %s", str());
	

	return 0;
}

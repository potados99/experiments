#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASSIGN_IF_OR(X, WHEN, DO) \
	({ __auto_type _result = (X); if (!(_result WHEN)) { DO; } (_result WHEN) ? _result : 0; })

int main(int argc, const char * argv[]) {
	// insert code here...
	
	int a = ASSIGN_IF_OR(36, > 10, printf("Gotta be more than 10 !!\n"); return -1);
	printf("a is %d\n", a);

	int b = ASSIGN_IF_OR(3, > 5, printf("Gotta be more than 5 !!\n"); return -1);
	printf("b is %d", b);


	return 0;
}

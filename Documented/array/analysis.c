#include "analysis.h"

void analysis_on_array() {
	printf("td_arr is a (char [%d][%d]) type array.\n\n", ROWS, COLUMNS);

        char td_arr[ROWS][COLUMNS] = {
                {'a', 'b', 'c', 'd', 'e', 'f', '\0'},
                {'g', 'h', 'i', 'j', 'k', 'l', '\0'},
                {'m', 'n', 'o', 'p', 'q', 'r', '\0'},
                {'s', 't', 'u', 'v', 'w', 'x', '\0'},
                {'y', 'z', '1', '2', '3', '4', '\0'}
        };

	print_td_array(&td_arr[0][0], ROWS, COLUMNS);
        printf("\n");

        printf("td_arr                  is %x | size is %ld\n", td_arr, sizeof(td_arr));
        printf("td_arr + 1              is %x | size is %ld\n", td_arr + 1, sizeof(td_arr + 1));
        printf("\n");

        printf("&td_arr                 is %x | size is %ld\n", &td_arr, sizeof(&td_arr));
        printf("&td_arr + 1             is %x | size is %ld\n", &td_arr + 1, sizeof(&td_arr + 1));
        printf("\n");

        printf("td_arr[0]               is %x | size is %ld\n", td_arr[0], sizeof(td_arr[0]));
        printf("td_arr[0] + 1           is %x | size is %ld\n", td_arr[0] + 1, sizeof(td_arr[0] + 1));
        printf("\n");

        printf("&td_arr[0]              is %x | size is %ld\n", &td_arr[0], sizeof(&td_arr[0]));
        printf("&td_arr[0] + 1          is %x | size is %ld\n", &td_arr[0] + 1, sizeof(&td_arr[0] + 1));
        printf("\n");

        printf("&td_arr[0][0]           is %x | size is %ld\n", &td_arr[0][0], sizeof(&td_arr[0][0]));
        printf("&td_arr[0][0] + 1       is %x | size is %ld\n", &td_arr[0][0] + 1, sizeof(&td_arr[0][0] + 1));
        printf("\n");
}

void analysis_on_types() {
        printf("Size of char            is %ld\n",sizeof(char));
        printf("Size of short           is %ld\n",sizeof(short));
        printf("Size of int             is %ld\n",sizeof(int));
        printf("Size of float           is %ld\n",sizeof(float));
        printf("Size of long            is %ld\n",sizeof(long));
        printf("Size of long int        is %ld\n",sizeof(long int));
        printf("Size of long long       is %ld\n",sizeof(long long));
        printf("Size of double          is %ld\n",sizeof(double));
        printf("Size of long long int   is %ld\n",sizeof(long long int));
}

void print_td_array(char *array, int rows, int columns) {
	for (int i = 0; i < rows; ++ i) {
		printf("{");
		for (int j = 0; j < columns; ++ j) {
			char charString[2];
			charString[0] = *(array + (i * columns) + j);
			charString[1] = '\0';

			printf("'%s'%s", charString[0] ? charString : "\\0", (j < columns - 1) ? ", " : "");
		}
		printf("}%s", (i < rows - 1) ? ",\n" : "\n");
	}
}

/**
 * 201701562 Song Byeong Jun
 * necho
 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int get_dec_long(char *token, long *result);

int main(int argc, char * const argv[]) {
	extern char 	*optarg;
	extern int 	optind, optopt;

	const char *short_opt = "r:";
	struct option long_opt[] = {
		{"repeat", required_argument, NULL, 'r'}
	};

	int 		op;
	long 		repeat = 1; /* default one time */

	/**
	 * getopt moves unhandled arguments after options.
	 * for example,
	 * if user typed './necho hello world -r 2' or './necho hello -r 2 world',
	 * argv gets sorted by getopt like below:
	 *	argv[0]: ./necho
	 *	argv[1]: -r
	 *	argv[2]: 2
	 *	argv[3]: hello
	 *	argv[4]: world
	 * in this case optind is 3, pointing the start of non-option argument.
	 */
	while ((op = getopt_long(argc, argv, short_opt, long_opt, NULL)) != -1) {
		switch (op) {
			case 'r':
				if (get_dec_long(optarg, &repeat) != 0 || repeat < 0) {
					fprintf(stderr, "invalid argument for option 'r'.\n");
					return -1;
				}
				break;

			case '?':
				if (optopt == 'r') {
					fprintf(stderr, "option 'r' requires number.\n");
				}
				goto usage;

			default:
				goto usage;
		}
	}

	for (int i = 0; i < repeat; ++i) {
		for (int j = optind; j < argc; ++j) {
			printf("%s ", argv[j]);
		}
		puts("");
	}

	return 0;

	/* wrong use handle routine. */
	usage:
	printf("Usage: necho [options] text...\n");
	printf("Options:\n");
	printf("\t-r, --repeat <times>\t Repeat output.\n");

	return -1;
}

int get_dec_long(char *token, long *result) {
	char *end;
	long dec;

	dec = strtol(token, &end, 10);

	if (*end != '\0') {
		fprintf(stderr, "invalid number '%s'\n", token);
		return -1;
	}
	if (end == token) {
		fprintf(stderr, "invalid number: empty string.\n");
		return -1;
	}

	*result = dec;

	return 0;
}

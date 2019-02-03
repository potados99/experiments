#include "fork.h"

void fork_test() {
        printf("\t\tHello, I am %d.\n", getpid());

        printf("\t\tI will make my child.\n");

        printf("\t\tKAAAAAAAAA!!\n");

        int pidfirst = fork();

        if (pidfirst == 0) {
                printf("\t\t\tOh...Hello mama..I am.. %d, right?\n", getpid());
                printf("\t\t\tThis world is so beautiful...But I have to go.. bye mama... bye %d..\n", getppid());
                exit(0);
        }
        else {
                printf("\t\t\tHey,,! You are born!, My child %d !\n", pidfirst);
                usleep(500); // waiting for child responding
        }
}

void fork_increase_test() {
	int pid1;
	int pid2;

	printf("\t\tWe are at first branch point.\n");
	pid1 = fork();
	if (pid1 == 0) {
		printf("\t\t\tParent(%d) made child 1(%d)!\n", getppid(), getpid());
	}
	else {
		printf("\t\t\tParent keeps going after making child 1.\n");
	}

	printf("\t\tWe are at second branch point.\n");
	pid2 = fork();
	if (pid2 == 0) {
		if (pid1 == 0) {
			printf("\t\t\tchild 1(%d) made child 2(%d)!\n", getppid(), getpid());
		}
		else {
			printf("\t\t\tParent(%d) made child 2(%d)!\n", getppid(), getpid());
		}
	}
	else {
		if (pid1 == 0) {
			printf("\t\t\tChild 1 keeps going after making child 2.\n");
		}
		else {
			printf("\t\t\tParent keeps going after making child 2.\n");
		}
	}

	if (pid1 && pid2) {
		// parent
		printf("\t\t\tParent finished.\n");
	}
	else if (pid2 == 0) {
		if (pid1 == 0) {
			printf("\t\t\tChild 2 (by child 1) finished.\n");
		}
		else {
			printf("\t\t\tChild 2 (by parent) finished.\n");
		}
	}
	else if (pid1 == 0) {
		printf("\t\t\tChild 1 finished.\n");
	}
}


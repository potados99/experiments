#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, const char * argv[]) {
        int pid = (int)getpid();

        kill(pid, SIGSTOP);
        kill(pid, SIGCONT);

        printf("Shall this line be printed\n");

	return 0;
}

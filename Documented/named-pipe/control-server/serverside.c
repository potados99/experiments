#include "serverside.h"
#include "serial.h"

extern int serialfd;
extern const char *tempDir;

void action(char *recieved) {
	char pid[PIDBUF_SIZE] = {0,};
	char cmd[CMDBUF_SIZE] = {0,};
	char feedback[CMDBUF_SIZE] = {0,};
	int resfd;

	divide(recieved, pid, DIVIDER, cmd);

	resfd = open_res_pipe(pid);

	serial_send(serialfd, TERMINATE, cmd, feedback, sizeof(feedback)); // send command and recieve feedback

        ipc_write(resfd, TERMINATE, feedback); // pass the feedback to client

        close(resfd);
}

int open_res_pipe(const char *pid) {
	char pidfifo[32] = {0,};

	join(pidfifo, tempDir, pid);
	return open_pipe(pidfifo, O_RDWR);
}



#include "serverside.h"

int serialfd = -1;
const char *tempDir;

int main(int argc, const char * argv[]) {
	if (argc < 4) {
		printf("Too less arguments!\n");
		printf("Usage: [executable] [temp directory] [serial port] [baudrate]\n");
		return 1;
	}

	// get arguments
	tempDir = argv[1];
	const char *serialPort = argv[2];
	int baudrate = atoi(argv[3]);
	printf("Program loaded.\n temp directory: %s\n serial port: %s\n baudrate: %d\n", tempDir, serialPort, baudrate);

	// open serial port
	serialfd = serial_open(serialPort, baudrate);
	printf("Serial port opened at %s.\n", serialPort);

	// recreate req fifo pipe file
	char reqFifoPath[32] = {0,};
	join(reqFifoPath, tempDir, REQ_PIPE_NAME);
        remove_pipe(reqFifoPath);
        make_pipe(reqFifoPath);

	// open
        int listenfd = open_pipe(reqFifoPath, O_RDWR | O_NONBLOCK);
	printf("Opened request pipe at %s.\n", reqFifoPath);

	// listen
	struct listenparam params;
	params.fd = listenfd;
	params.delim = TERMINATE;
	params.behavior = L_KEEP | L_CLBCK;
	params.callback = action;

	printf("Start listening.\n");
        ipc_listen(params);

        return 0;
}


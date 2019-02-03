#include "ipc.h"

void ipc_listen(struct listenparam param) {
	char rbuf[64];
	memset(rbuf, 0, sizeof(rbuf));

	for (;;) {
		if (ipc_read(param.fd, param.delim, rbuf, sizeof(rbuf)) < 1) continue;

		if (param.behavior & L_CLBCK) param.callback(rbuf);
		if (~param.behavior & L_KEEP) return;
	}
}

int ipc_read(int fd, char delim, char *rbuf, unsigned int rbufSize) {
	memset(rbuf, 0, rbufSize); // reset buffer. I'm so kind.

	char *rbufPtr = rbuf;
	int rbytes;

	int cnt = 0;

	while ((rbytes = read(fd, rbufPtr, 1)) > 0) {
		rbufPtr += rbytes;
		if (rbufPtr[-1] == delim || cnt > 50) break;
	} rbufPtr[-1] = '\0'; // remove delim

	return rbytes;
}

int ipc_write(int fd, char delim, const char *wbuf) {
	char buf[IPC_WBUF_SIZE] = {0,};
	memcpy(buf, wbuf, strlen(wbuf));
	buf[strlen(buf)] = delim; // add delimiter to the end of the write buffer.

	int wbytes;
	int bufLen = strlen(buf);
	if ((wbytes = write(fd, buf, bufLen)) != bufLen) ERROR("Failed writing data.\n");

	return wbytes;
}

int open_pipe(const char *name, int mode) {
	int fd;
	if ((fd = open(name, mode)) < 0) ERRORF("Failed opening fifo file: %s\n", name);

	return fd;
}

void make_pipe(const char *name) {
	if (mkfifo(name, 0644) == -1) ERRORF("Failed creating fifo file: %s\n", name);
}

void remove_pipe(const char *name) {
	if (unlink(name)) ERRORF("Failed removing %s\n", name);
}

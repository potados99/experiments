#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include <linux/input-event-codes.h>

#define EVENTPATH "/dev/input/event1"
#define READ_X	0x01
#define READ_Y	0x02
#define READ_P	0x04

struct touch_event {
	int x;
	int y;
	int pressure;
};

int touch_read(int fd, struct touch_event *event) {
	struct input_event ie;
	int done = 0; /* initialization necessary! */

	while (done != (READ_X | READ_Y | READ_P)) {

		if (read(fd, &ie, sizeof(struct input_event)) < 0) {
			perror("read error");
			return -1;
		}

		if (ie.type == EV_ABS) {
			if (ie.code == ABS_X) {
				event->x = ie.value;
				done |= READ_X;
			}
			else if (ie.code == ABS_Y) {
				event->y = ie.value;
				done |= READ_Y;
			}
			else if (ie.code == ABS_PRESSURE) {
				event->pressure = ie.value;
				done |= READ_P;
			}
		} 

	}

	return 0;
}

int main(int argc, char *argv[]) {
	int fd;
	struct touch_event te;
	int x;
	int y;
	int pressure;

	//fd = open(EVENTPATH, O_RDONLY | O_NONBLOCK);
	fd = open(EVENTPATH, O_RDONLY);
	if (fd < 0) return -1;

	int count = 0;
	while (count++ < 1000) {

		if (touch_read(fd, &te) == 0)
			printf("x: %d, y: %d, pressure: %d\n", te.x, te.y, te.pressure);
	}

	printf("hello world.\n");

	close(fd);

	return 0;
}	

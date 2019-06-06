#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h> 
#include <linux/fb.h> 
#include <sys/mman.h>
#include <time.h>

#define FD_PATH "/dev/fb2"

#define PIXEL(R, G, B) 						\
	(((R >> 3) << 11) | ((G >> 2) << 5) | (B >> 3))

static inline void draw_pixel(unsigned short *data_ptr, int x, int y, unsigned short color) {
	int offset = (y * 320) + x;
	*(data_ptr + offset) = color;
}

static inline void draw_rect(unsigned short *data_ptr, int x, int y, int width, int height, unsigned short color) {
	int offset = (y * 320) + x;

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			*(data_ptr + offset + (320 * i) + j) = color;
		}
	}
}

static inline unsigned short rand_pixel() {
	static int s = 0;
	srand(time(NULL) + s++);
	int r, g, b;
	r = rand() % 256;
	srand(time(NULL) + s++);
	g = rand() % 256;
	srand(time(NULL) + s++);
	b = rand() % 256;

	return PIXEL(r, g, b);
}

int main(int argc, char const* argv[]) {

	int fd;
	unsigned short pixel;
	unsigned short *data;

	fd = open(FD_PATH, O_RDWR);
	if (fd < 0) {
		perror("error while open()");
		exit(1);
	}

	/* assume that LCD is okay. :) */

	data = (unsigned short *)mmap(NULL, 320 * 240 * 2, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (data == MAP_FAILED) {
		perror("error while mmap()");
		exit(1);	
	}	

	int s = 0;
	srand(time(NULL) + s++);

	unsigned short p;

	

	// clear
	draw_rect(data, 0, 0, 320, 240, rand_pixel());
	
	int x, y, w, h;
	
	for (int i = 0; i < 10; ++i) {
		srand(time(NULL) + s++);
		x = rand() % 320;
		srand(time(NULL) + s++);
		y = rand() % 240;
		
		srand(time(NULL) + s++);
		w = rand() % (320 - x);
		srand(time(NULL) + s++);
		h = rand() % (240 - y);
		srand(time(NULL) + s++);

		draw_rect(data, x, y, w, h, rand_pixel());	
	}

	// draw_rect(data, 20, 50, 200, 150, PIXEL(0, 128, 128));

	munmap(data, 320 * 240 * 2);

	close(fd);

	return 0;
}

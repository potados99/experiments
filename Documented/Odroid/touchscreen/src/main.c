#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "metric.h"
#include "touch.h"
#include "display.h"

void calibrate(unsigned short *dp_mem, int ts_fd,struct touch_correction *correction);

int main(int argc, char *argv[]) {
	int 				ts_fd;
	int 				dp_fd;
	unsigned short 			*mem;
	struct touch_correction 	correction;

	/**
	  * Ready
	  */
	dp_fd = open(FDPATH, O_RDWR);
	if (dp_fd < 0) return -1;

	ts_fd = open(EVENTPATH, O_RDONLY); /* do blocking read. */
	if (ts_fd < 0) return -1;

	printf("opened fds.\n");

	mem = disp_map(dp_fd);

	printf("mapped.\n");

	disp_draw_rect(mem, 0, 0, DISP_WIDTH, DISP_HEIGHT, PIXEL(0, 0, 0));

	calibrate(mem, ts_fd, &correction);
	
	

	disp_unmap(mem);

	close(dp_fd);
	close(ts_fd);

	return 0;
}	

void calibrate(unsigned short *dp_mem, int ts_fd, struct touch_correction *correction) {
	struct point lcd_points[3] = {
		{160, 80}, {80, 160}, {240, 160}
	};

	struct point ts_points[3];
	struct touch_event te;

	for (int i = 0; i < 3; ++i) {
		disp_draw_rect(dp_mem, lcd_points[i].x - 1, lcd_points[i].y - 1, 3, 3, PIXEL(255, 255, 255));

		if (touch_read(ts_fd, &te, NULL) != 0) {
			printf("touch_read error!\n");
			exit(1);
		}

		ts_points[i].x = te.x;
		ts_points[i].y = te.y;

		usleep(1000000);
	}
	
	int k = ((ts_points[0].x - ts_points[2].x) * (ts_points[1].y - ts_points[2].y)) - 
		((ts_points[1].x - ts_points[2].x) * (ts_points[0].y - ts_points[2].y));

	correction->xd_coef_x = (((lcd_points[0].x - lcd_points[2].x) * (ts_points[1].y - ts_points[2].y)) - 
			((lcd_points[1].x - lcd_points[2].x) * (ts_points[0].y - ts_points[2].y))) / k;
	
	correction->xd_coef_y = (((ts_points[0].x - ts_points[2].x) * (lcd_points[1].x - lcd_points[2].x)) - 
			((lcd_points[0].x - lcd_points[2].x) * (ts_points[1].x - ts_points[2].x))) / k;
 
	correction->xd_coef_1 = ((ts_points[0].y * ((ts_points[2].x * lcd_points[1].x) - (ts_points[1].x * lcd_points[2].x))) + 
			(ts_points[1].y * ((ts_points[0].x * lcd_points[2].x) - (ts_points[2].x * lcd_points[0].x))) + 
			(ts_points[2].y * ((ts_points[1].x * lcd_points[0].x) - (ts_points[0].x * lcd_points[1].x)))) / k;
	

	correction->yd_coef_x = (((lcd_points[0].y - lcd_points[2].y) * (ts_points[1].y - ts_points[2].y)) - 
			((lcd_points[1].y - lcd_points[2].y) * (ts_points[0].y - ts_points[2].y))) / k;
	
	correction->yd_coef_y = (((ts_points[0].x - ts_points[2].x) * (lcd_points[1].y - lcd_points[2].y)) - 
			((lcd_points[1].y - lcd_points[2].y) * (ts_points[1].x - ts_points[2].x))) / k;
	
	correction->yd_coef_1 = ((ts_points[0].y * ((ts_points[2].x * lcd_points[1].y) - (ts_points[1].x * lcd_points[2].y))) + 
			(ts_points[1].y * ((ts_points[0].x * lcd_points[2].y) - (ts_points[2].x * lcd_points[0].y))) + 
			(ts_points[2].y * ((ts_points[1].x * lcd_points[0].y) - (ts_points[0].x * lcd_points[1].y)))) / k;
}


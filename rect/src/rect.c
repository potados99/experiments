#include "rect.h"

/*
struct point {
	int x;
	int y;
};

struct rect {
	struct point top_left;
	struct point bottom_right;
};

*/

#include <stdio.h>

void print_rect(const struct rect *rt) {
	for (int v_offset = 0; v_offset < rt->top_left.y; ++v_offset) putc('\n', stdout); /* vertical offset */

	for (int r = 0; r < height(rt); ++r) {
		for (int c_offset = 0; c_offset < rt->top_left.x; ++c_offset) putc(' ', stdout); /* horizontal offset */
		for (int c = 0; c < width(rt); ++c) putc('*', stdout);
		putc('\n', stdout);
	} 
}

int width(const struct rect *rt) {
	return (rt->bottom_right.x - rt->top_left.x);
}

int height(const struct rect *rt) {
	return (rt->bottom_right.y - rt->top_left.y);
}

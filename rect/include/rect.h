#ifndef _RECT_H
#define _RECT_H


struct point {
	int x;
	int y;
};

struct rect {
	struct point top_left;
	struct point bottom_right;
};

void print_rect(const struct rect *rt);
int width(const struct rect *rt);
int height(const struct rect *rt);


#endif /* _RECT_H */

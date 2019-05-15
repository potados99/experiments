#include "ringbuf.h"

#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <error.h>
#include <errno.h>

/*
struct ringbuf {
	int *buf_ptr;
	int idx_front;
	int idx_end;
	int cap;
	int count
};

typedef struct ringbuf rbuf_t;
*/

int rb_init(rbuf_t *buf, int capacity) {
	if (buf == NULL || capacity < 0) return EINVAL; /* invalid argument */

	buf->cap = capacity + 1; /* in fact capacity is N but buffer size is N + 1. */
	buf->buf_ptr = (int *)malloc(sizeof(int) * buf->cap + 1);
	if (buf->buf_ptr == NULL) {
		int e = errno;
		perror("error while malloc() for buf->buf_ptr");
		return e;
	}

	buf->idx_front = 0;
	buf->idx_end = 0;
	buf->count = 0;

	return 0;
}

int rb_free(rbuf_t *buf) {
	if (buf == NULL) return EINVAL; /* invalid argument */
	
	free(buf->buf_ptr);

	return 0;
}

int rb_is_empty(rbuf_t *buf) {	
	if (buf == NULL) return EINVAL; /* invalid argument */
	
	return (buf->idx_front == buf->idx_end);
}

int rb_is_full(rbuf_t *buf) {
	if (buf == NULL) return EINVAL; /* invalid argument */
	
	return ((buf->idx_end + 1) % buf->cap == buf->idx_front); /* 'front' is right after 'end'. */
}

int rb_push(rbuf_t *buf, int val) {
	if (buf == NULL) return EINVAL; /* invalid argument */
	
	if (rb_is_full(buf)) {
		error(0, EPERM, "rb_pop: buffer is empty");
		return EPERM; /* operation not permitted. */
	}

	buf->idx_end = (buf->idx_end + 1) % buf->cap;
	*(buf->buf_ptr + buf->idx_end) = val;
	
	return 0;
}

int rb_pop(rbuf_t *buf) {
	if (buf == NULL) return EINVAL; /* invalid argument */

	if (rb_is_empty(buf)) {
		error(0, EPERM, "rb_pop: buffer is empty");
		return EPERM;
	}

	buf->idx_front = (buf->idx_front + 1) % buf->cap;

	return *(buf->buf_ptr + buf->idx_front);
}

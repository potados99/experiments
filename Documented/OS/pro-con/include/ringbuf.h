#ifndef _ringbuf_h
#define _ringbuf_h

struct ringbuf {
	int *buf_ptr;
	int idx_front;
	int idx_end;
	int cap;
	int count;
};

typedef struct ringbuf rbuf_t;

int rb_init(rbuf_t *buf, int capacity);
int rb_free(rbuf_t *buf);

int rb_is_empty(rbuf_t *buf);
int rb_is_full(rbuf_t *buf);

int rb_push(rbuf_t *buf, int val);
int rb_pop(rbuf_t *buf);

#endif /* _ringbuf_h */

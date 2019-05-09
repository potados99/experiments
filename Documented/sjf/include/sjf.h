#ifndef _sjf_h
#define _sjf_h

#include "list.h"

struct task {
	char name[64];
	int tm_arrive;
	int tm_burst;

	struct list_head list;
};

/*
struct task_queue {
	struct list_head front;
	int size;
}
*/

struct task *task_alloc(struct task t);

void task_enqueue(struct list_head *queue, struct task *t);
struct task *task_dequeue(struct list_head *queue);

void simulate_task_arrive();
void process_task();


#endif /* _sjf_h */

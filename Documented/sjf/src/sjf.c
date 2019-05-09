/*

struct task {
	char name[64];
	int tm_arrive;
	int tm_burst;

	struct list_head list;
};

 */

#include "sjf.h"

#include <stdlib.h>
#include <string.h>

struct task *task_alloc(struct task t) {
	struct task *alloced = (struct task *)malloc(sizeof(struct task));

	*alloced = t;

	alloced->list.next = &(alloced->list);
	alloced->list.prev = &(alloced->list); /* not necessary */
	
	return alloced;
}

void task_enqueue(struct list_head *queue, struct task *t) {
	list_add_tail(&(t->list), queue);
}

struct task *task_dequeue(struct list_head *queue) {
	if (list_empty(queue)) return NULL;

	struct task *front = list_entry(queue->next, struct task, list);
	// content starts from head->next.

	list_del(queue->next);
	
	return front;
}

void simulate_task_arrive() {

}

void process_task() {

}



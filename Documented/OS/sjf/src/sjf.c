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

	struct task *front = list_first_entry(queue, struct task, list);
	// content starts from head->next.

	list_del(&(front->list));
	
	return front;
}

struct task *task_dequeue_prio(struct list_head *queue) {
	if (list_empty(queue)) return NULL;

	struct task *most_prio = list_first_entry(queue, struct task, list);
	struct task *pos;
	list_for_each_entry(pos, queue, list) {
		if (pos->tm_burst < most_prio->tm_burst) {
			most_prio = pos;
		}
	}

	list_del(&(most_prio->list));

	return most_prio;
}

void simulate_task_arrive(int cur_time, struct list_head *ready_queue, struct list_head *future) {
	if (list_empty(future)) return;

	int found = 0;
	struct task *pos;
	list_for_each_entry(pos, future, list) {
		if (pos->tm_arrive == cur_time) {
			found = 1;
			break;
		}
	}

	if (found) {
		printf("at time %d: new task arrived: %s.\n", cur_time, pos->name);
		struct list_head *node = &(pos->list);
		list_move_tail(node, ready_queue);
	}
}

void process_task(int cur_time, struct task *cur_task) {
	printf("at time %d: processing %s: [%d/%d].\n", cur_time, cur_task->name, ++cur_task->progress, cur_task->tm_burst);
}

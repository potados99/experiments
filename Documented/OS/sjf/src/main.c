#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// 자작 입출력 라이브러리
#include "pio.h"

// 자작 문자열 처리 라이브러리(?)
#include "strutil.h"

// 태스크 자료구조와 처리 루틴
#include "sjf.h"

int on_file_read(const char *file_content, int len);
int add_tasks(const char *line, int len);

LIST_HEAD(task_queue);
LIST_HEAD(future_queue);

int main(int argc, const char * argv[]) {
	// 인자 췤!
	if (argc != 2) goto usage; 
	
	// 샘플 파일 읽어서 task를 쟁여놓습니다. 대기 큐에 바로 들어가는 것은 아님.
	p_with_file(argv[1], on_file_read);

	int time = 0;
	struct task *cur_task = NULL;

	while (!list_empty(&future_queue) || !list_empty(&task_queue) || cur_task != NULL) {
		simulate_task_arrive(time, &task_queue, &future_queue);
		
		if (cur_task == NULL || cur_task->progress >= cur_task->tm_burst) {
			// time to get new
			if (cur_task) {
				printf("at time %d: task %s is done.\n", time, cur_task->name);
				free(cur_task);
			}
			if (list_empty(&task_queue)) {
				cur_task = NULL;
			}
			else {
				cur_task = task_dequeue_prio(&task_queue);
				printf("at time %d: next task is %s.\n", time, cur_task->name);
			}
		}
		
		if (cur_task) {
			process_task(time, cur_task);
		}

		usleep(100000);
		time++;
	}



	return 0;


/************** Wrong arguments ***************/
usage:
	puts("Usage:");
	puts("sjf [process data file]");

	return -1;
/**********************************************/

}

int on_file_read(const char *file_content, int len) {
	split_foreach(file_content, len, '\n', add_tasks);

	return 0;
}

int add_tasks(const char *line, int len) {
	if (len >= 2 && line[0] == '/' && line[1] == '/') return 0;

	char name[32];
	char tm_arrive[32];
	char tm_burst[32];

	sscanf(line, "%[^:]:%[^:]:%s", name, tm_arrive, tm_burst); /* yeah */
	
	struct task t;
	sprintf(t.name, "%s", name);
	t.tm_arrive = atoi(tm_arrive);
	t.tm_burst = atoi(tm_burst);
	t.progress = 0;

	task_enqueue(&future_queue, task_alloc(t));

	return 0;
}

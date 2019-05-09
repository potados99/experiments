#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 자작 입출력 라이브러리
#include "pio.h"

// 자작 문자열 처리 라이브러리(?)
#include "strutil.h"

#include "sjf.h"

int on_file_read(const char *file_content, int len);
int add_tasks(const char *line, int len);

int main(int argc, const char * argv[]) {
	// 인자 췤!
	if (argc != 2) goto usage; 
	
	p_with_file(argv[1], on_file_read);

	struct task tarr[] = {
		{"t1", 2 ,4},
		{"t2", 3, 9},
		{"t3", 4, 1},
		{"hello", 5, 6}
	};

	LIST_HEAD(task_queue);

	for (int i = 0; i < sizeof(tarr) / sizeof(struct task); ++i) {
		task_enqueue(&task_queue, task_alloc(tarr[i]));
	}

	while(!list_empty(&task_queue)) {
		struct task *t = task_dequeue(&task_queue);
		if (t == NULL) continue;

		printf("dequeue: %s:%d:%d.\n", t->name, t->tm_arrive, t->tm_burst);
		free(t);
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
	printf("total: %d chars: [%s]\n", len, file_content);
	
	split_foreach(file_content, len, '\n', add_tasks);

	return 0;
}

int add_tasks(const char *line, int len) {
	printf("read: %d bytes, content: \n[%s]\n", len, line);
	
	return 0;
}

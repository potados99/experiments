#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>

/**
  오늘 쓸 함수들이 있는데요,
  어디 한번 매뉴얼을 봅시다.
  
  int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg) 
  요건 스레스 새로 만들 때 쓸거구요,

  void perror(const char *s);
  요건 에러 토할때 쓸겁니다.
  */


/**
  쉽고 빠르게 예외상황 처리를 해줄 녀석입니다.
  */
#define assert(CONDITION, DO) 		\
	do {				\
		if (!(CONDITION)) {	\
			DO;		\
		}			\
	} while(0)			


/**
  게으른 프로그래머를 위한 매크로입니다.
  */
#define arg_t int

#define ARG_FMT "%d"
#define ARG_PACK(ARG) (&(ARG))
#define ARG_UNPACK(ARG) (*((arg_t *)ARG))


/**
  pthread 새로 만들 때 가져다 쓸 녀석입니다.
  */
void *thread_callback(void *arg);


int main(int argc, char **argv) {
	pthread_t tid;
	int result;
	int arg = 36;

	/* 생성 */
	result = pthread_create(&tid, NULL, thread_callback, ARG_PACK(arg));	
	assert(result == 0, perror("pthread_create()"); return -1); /* 조건이 zero로 나오면 에러 출력하고 반환! */

	/* 메인 스레드가 할 일 */
	for (int i = 0; i < 2; ++ i) {
		printf("from main thread: counting %d.\n", i);
		sleep(1);
	}
	puts("main thread is done. waiting for new thread.");

	/* 조-인 */	
	result = pthread_join(tid, NULL); /* blocking */
	assert(result == 0, perror("pthread_join()"); return -1);

	puts("main thread reaching its end!");

	return 0;
}

void *thread_callback(void *arg) {
	arg_t arg_data = ARG_UNPACK(arg);
	printf("argument from main thread: " ARG_FMT "\n", arg_data);
	
	/* 새 스레드가 할 일 */
	for (int i = 0; i < 3; ++i) {
		printf("from new thread: counting %d.\n", i);	
		sleep(1);
	}

	return NULL;
}

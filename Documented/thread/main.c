#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>>
#include <pthread.h>

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
#define ARG_TYPE int
#define ARG_TYPE_PRIMITIVE


/**
  pthread 새로 만들 때 가져다 쓸 녀석입니다.
  */
void thread_callback(void *arg);


int main(int argc, char **argv) {
	



	return 0;
}

void thread_callback(void *arg) {
#if (ARG_TYPE_PRIMITIVE > 0) 
	ARG_TYPE arg_data = 

#endif

}

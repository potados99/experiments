//201701550 남지원//
#include <stdio.h>
#include <stdlib.h>

/////////////////////////////////////// 주목 /////////////////////////////////////
// #define DEBUG

void mylog(const char *msg) {
#ifdef DEBUG
	printf("	LOG: %s\n", msg);
#endif
}
/////////////////////////////////////////////////////////////////////////////////

/*
 
 1. 동적 배열 스택 구현
 
 */

//구조체를 이용해서 동적 스택을 구현한다.
typedef int element;
typedef struct {
    element *data;//스택 안의 요소들.
    
    int capacity;//현재 스택의 크기.
    int top;//스택의 가장 위의 값.

}StackType;
//스택 초기화 메소드 : top의 초기값은 스택이 비어있으므로, -1이고, 처음 크기는 5로 설정함.
void init_stack(StackType *s){
    s ->top = -1;
    s ->capacity = 5;
	////////////////////////////////////////////////////////////////////// OH MY GOD /////////////////////////////////////////////
	
	s ->data = (element *)malloc(s ->capacity * sizeof(element) + 1); /* 1 for safety. */
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

//스택 공백 메소드 : "top이 -1이면 공백이다." 라고 정의했으므로 top이 -1이면, 즉 공백 상태이면 1을 반환한다.
int is_empty(StackType *s){
    return (s ->top == -1);
}
//스택 포화 메소드 : 현재 배열의 인덱스중 가장 큰 수와 top이 일치하면 그 스택은 "포화" 상태이다.
int is_full(StackType *s){
    return (s ->top == (s ->capacity - 1));
}
/*
 push 메소드 : 조건문을 사용한다.
 만약 스택이 포화상태라면 현재 스택의 크기를 2배 더 늘리고,
 (스택의 크기) x (element의 사이즈) 만큼의 메모리를 할당한다.
 그게 아니라면, 전위 연산자를 통하여 증가된 top에 item을 추가한다.
 */
void push(StackType *s, element item){
  	mylog("entered push function.");

	mylog("is this stack full?");
    if (is_full(s)) {
		mylog("yes it is full.");
        s ->capacity *= 2;
		mylog("lets realloc it.");
        s ->data = (element*)realloc(s ->data, s ->capacity * sizeof(element));
		mylog("realloc is done.");
	}

	mylog("lets add one to the top.");
    s ->data[++(s ->top)] = item;
	mylog("push success.");
	
	mylog("returning from push function.");
}
/*
 pop 메소드 : 조건문을 사용한다.
 만약 스택이 공백상태라면 에러메세지를 출력하고,
 그것이 아니라면 현재 top의 값을 반환하고 후위연산자로 top숫자를 하나 감소시킨다.
 */
element pop(StackType *s){
   
    if (is_empty(s)) {
        fprintf(stderr, "underFlow ERROR\n");
        exit(1);
        
    }else
        return s ->data[(s ->top)--];
}

/*
 
 2. 더블 스택드 큐 구현
 
 */

/*
 스택 두개로 큐를 구현하는 방법은 생각만 한다면 간단하게 구현이 가능하다.
 선입후출인 스택 하나를 전부 pop시켜 다른 하나의 스택에 push를 하면 선입선출이 가능한 큐 구조가 된다.
 이 스택 두개를 간단히 전스택, 후스택으로 칭하자.
 */

//enqueue 메소드 : 그저 전스택에 item을 push하는 과정이다.
void enqueue(StackType *s, element item){
 	mylog("entered enqueue function.");
	push(s, item);
	mylog("push successful.");
	mylog("returning from enqueue function.");
}
/*
 dequeue 메소드 : 이것이 조금 복잡한데, 전스택에 있는 데이터를 모두 pop하여 후스택에 push하는 과정이다.
 이 과정을 전스택이 공백일때까지 반복한다.
 에러메세지는 이미 pop메소드에서 선언했으니 따로 추가할 필요는 없다.
 */
element dequeue(StackType *first, StackType *second){
    mylog("entered dequeue function.");

    while (!is_empty(first)) {
        mylog("first is not empty. (still)");
		element it = pop(first);
		mylog("popped element from first.");
        push(second, it);
		mylog("pushed it to second.");
    }
	mylog("transfer success.");

    element result = pop(second);
	mylog("popped final result from second.");

	mylog("returning from dequeue function.");

    return result;
}
/*
 
 3. 소수 판별 및 메인 메소드
 
 */

/*
 소수 판별 메소드 : 상당히 간단한 검사기이다.
 어떤 수가 2이상의 자연수로 나누어 떨어지면 그 수는 소수가 아닌수임을 이용했다.
 추가로, 이 문제에서는 10이상의 수를 원했으므로 그것도 판별한다.
 */
int is_prime(int n){
    if (n == 1) {
        return 0;
    
    }
    else{
        for (int i = 2; i <= n; i++) {
            if (n % i == 0 || n < 10) {
                return 0;
            }
        }
        return 1;
    }
}
//메인 메소드.
int main() {
   
    StackType *s1, *s2;//더블 스택 선언.
    mylog("stack s1 and s2 declared.");

    s1 = (StackType*)malloc(sizeof(StackType));
    init_stack(s1);
	mylog("s1 alloc and init.");

    s2 = (StackType*)malloc(sizeof(StackType));
    init_stack(s2);
	mylog("s2 alloc and init.");

    //스택 2개를 각각 StackType의 만큼의 메모리를 할당하며 초기화한다.
    
    int n = 0;//입력 받을 변수 n이다.
    
    while (1) {//나는 한 번 질문을 받고 판별한 후, 계속해서 프로그램을 사용할 수 있도록 만들었다.
        
        printf("100이상의 정수를 입력해주세요 (종료하시려면 -1을 입력) : ");
		
		scanf("%d", &n);
        mylog("got input.");
		
		/*
         정상적으로 n이 입력받았다면 판별이 시작된다.
         i ->k가 소수라면 dequeue, 아니면 k를 enqueue.
         */
        if (n >= 100) {
            mylog("n >= 100, starting for loop.");

			for (int i = 1; i < n; i++) {
				mylog("	in the loop: is i a prime number?");
                if (is_prime(i)) {
					mylog("	yes, it is prime.");
                    printf("k : %d", dequeue(s1, s2));
					mylog("dequeue s1, s2.");
                    free(s1);
					mylog("freed s1.");
                    free(s2);
					mylog("freed s2.");
                }

				mylog("lets put i to s1.");
                enqueue(s1, i);
				mylog("successfully enqueued i to s1.");
			}
        }
        else if (n == -1){//n이 -1이면 종료한다.
            printf("\n종료...\n");
            break;
        }
        else{//n이 조건에 맞는 숫자가 아니면 다시 첫 질문으로 돌아온다.
            printf("올바른 수를 입력해주세요.\n\n");
        }
    }
}

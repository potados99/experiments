# 두 개의 세마포어로 구현한 생산자-소비자 문제 해결방법

## 상세
버퍼가 비었음을 나타내는 empty 세마포어와 점유되었음을 알리는 occupied 세마포어를 사용합니다.
생산자는 empty 세마포어가 사용 가능할 때에 버퍼에 값을 추가하며, 추가 후 occupied 세마포어를 1 증가합니다.(반환)
소비자는 occupied 세마포어가 사용 가능할 때에 버퍼에서 값을 가져오며, 모두 가져오면 empty 세마포어를 증가시켜서
생산자가 새로운 값을 추가할 수 있도록 합니다.

생산과 소비는 상호배제적으로, 하나가 완전히 끝나야 다른 동작이 이루어집니다.

## 소스
- main.c
- ringbuf.h: 배열로 구현한 원형 큐
- ringbuf.c
- pro.h: 생산자
- pro.c
- con.h: 소비자
- con.c
- shared.h: 전역 스코프 변수

## 기타
이 소스에서는 생산이 소비보다 조금 느립니다.

Makefile에서 BUF_SIZE를 수정할 수 있습니다.

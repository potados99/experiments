N = int(input('2 이상의 자연수 입력 : '))

while(N < 2):
    print(str(N) + '은(는) 2 이상의 자연수가 아닙니다.')
    N = int(input('2 이상의 자연수 입력 : '))

list = list(range(1,N+1))
size = N
print(list)

for i in range(2,size):
	for j in range(0, i + 1):
		if (list[j] % list[i] == 0):
	    	    list[j] = 0
	    	    #size -= 1



for l in range(0,size):
    if(list[l]):
        print(list[l], end=' ')

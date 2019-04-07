N = int(input("N = "))

currentNum = 1
currentLineLen = 1

N = N - currentLineLen
while(N > 0):

	# Line started.
	i = 1
	while(i <= currentLineLen):
		print(currentNum, end = ' ')
		currentNum = currentNum + 1
		i = i + 1

	print("")
	# Line finished.

	currentLineLen = currentLineLen * 2
	N = N - currentLineLen

print("left: " + str(N))

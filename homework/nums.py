
def machine_way(N):
	currentNum = 1
	currentNumColumn = 1
	currentLineLen = 1

	while (1):

		if (currentNum <= N):
			print(currentNum, end = ' ')

			if (currentNumColumn == currentLineLen):
				print()
				currentLineLen *= 2
				currentNumColumn = 0
			
			currentNum += 1	
			currentNumColumn += 1


		else:
			print()
			exit()


def fast_way(N):
	currentLineLen = 1
	currentNum = 1
	currentNumColumn = 1

	numsLeft = N

	while (numsLeft > 0):
		while (currentNumColumn <= currentLineLen):
			print(currentNum, end = ' ')
			currentNum += 1
			currentNumColumn += 1
		
		print()

		currentLineLen *= 2
		currentNumColumn = 1
		numsLeft -= currentLineLen

	if (numsLeft == 0):
		print()
		exit()
	else:
		while (currentNum <= N):
			print(currentNum, end = ' ')
			currentNum += 1
		print()
		exit()


def human_way(N):
	currentLineLen = 1
	currentNumColumn = 1

	for i in range(1, N + 1):
		print(i, end = ' ')

		if (currentNumColumn == currentLineLen):
			print()
			currentNumColumn = 1
			currentLineLen *= 2
		else:
			currentNumColumn += 1
	
	print()


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

fast_way(500000)


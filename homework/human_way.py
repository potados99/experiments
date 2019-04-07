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

human_way(500000)

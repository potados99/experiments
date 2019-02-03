# first way (138)
[print(str(dan) + " * " + str(index) + " = " + str(dan * index)) for index, dan in enumerate([int(input("come on: "))] * 10) if index > 0]

# second way (112)
[print(str(x) + " * " + str(y) + " = " + str(x * y)) for x in [int(input("come here: "))] for y in range(1, 10)]

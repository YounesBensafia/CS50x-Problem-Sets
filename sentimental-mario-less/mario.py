import cs50

while (True):
    input = int(cs50.get_int("Height: "))
    if (9 > input > 0):
        break

for i in range(input+1):
    if (i > 0):
        print(" " * (input - i) + "#" * i)

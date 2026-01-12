from cs50 import get_int

def numero():
    while True:
        heigth = get_int("Heigth: ")
        if(heigth > 0 and heigth < 9):
            break
    return heigth

heigth = numero()

for i in range(heigth):
    #print(" " * (heigth - (i + 1)) + "#" * (i + 1), end="  ")
    #print("#" * (i + 1))
    first = " " * (heigth - (i + 1)) + "#" * (i + 1)
    middle = "  "
    second = "#" * (i + 1)
    print(first + middle + second)

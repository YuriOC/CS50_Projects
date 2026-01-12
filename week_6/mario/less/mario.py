from cs50 import get_int

def numero():
    while True:
        heigth = get_int("Heigth: ")
        if (heigth >= 1 and heigth <= 8):
            break
    return heigth


heigth = numero()

for i in range(heigth):
    print(" " * (heigth - (i + 1)) + ("#" * (i + 1)))

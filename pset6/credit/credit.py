from cs50 import get_string

number = get_string("Number: ")
soma1 = []
soma2 = 0

if(len(number) != 13 and len(number) != 15 and len(number) != 16):
    print("INVALID")
else:
    for i in range(len(number) - 2, -1, -2):
        soma1 += f"{int(number[i]) * 2}"
    for i in range(len(soma1)):
        soma2 += int(soma1[i])
    for i in range(len(number) - 1, -1, -2):
        soma2 += int(number[i])

    if(soma2 % 10 != 0):
        print("INVALID")
    elif(number[0] == "4" and (len(number) == 13 or len(number) == 16)):
        print("VISA")
    elif(number[0] == "5" and number[1] in ["1", "2", "3", "4", "5"] and len(number) == 16):
         print("MASTERCARD")
    elif(number[0] == "3" and number[1] in ["3", "7"] and len(number) == 15):
        print("AMEX")
    else:
        print("INVALID")





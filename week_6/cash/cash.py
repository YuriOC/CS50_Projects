from cs50 import get_float

def value():
    while True:
        money = get_float("Change owed: ")
        if(money > 0):
            break
    return money

cent25 = 25
cent10 = 10
cent5 = 5
cent1 = 1

money = value() * 100
total = 0

while money >= cent25:
    money -= cent25
    total += 1

while money >= cent10:
    money -= cent10
    total += 1

while money >= cent5:
    money -= cent5
    total += 1

while money > 0:
    money -= cent1
    total += 1

print(total)



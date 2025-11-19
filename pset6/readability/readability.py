from cs50 import get_string

text = get_string("Text: ")
letters = 0
words = 1
sentences = 0

for i in range(len(text)):
    if (text[i].isalpha() == True):
        letters += 1
    if (text[i] == " "):
        words += 1
    if (text[i] == "." or text[i] == "!" or text[i] == "?"):
        sentences += 1

L = (float(letters) / float(words)) * 100
S = (float(sentences) / float(words)) * 100

CL = ((0.0588 * L) - (0.296 * S)) - 15.8

grade = int(CL * 10)

if (grade % 10 >= 5):
    grade = (grade / 10) + 1
else:
    grade = grade / 10

if (grade < 1):
    print("Before Grade 1")
elif (grade >= 1 and grade <= 16):
    print(f"Grade {grade}")
else:
    print("Grade 16+")

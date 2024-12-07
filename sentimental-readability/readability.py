import cs50
import string
input = cs50.get_string("Text: ")

lettre = 0
sent = 0
word = 0
input = input.lower()
for i in range(len(input)):
    if input[i] in ["a", "z", "e", "r", "t", "y", "u", "i", "o", "p", "q", "s", "d", "f", "g", "h", "j", "k", "l", "m", "w", "x", "c", "v", "b", "n"]:
        lettre = lettre + 1
    if input[i] == '.' or input[i] == '!' or input[i] == '?':
        sent = sent + 1
    if input[i] == " ":
        word = word + 1
word = word + 1
L = float((lettre * 100)) / (word)
S = float((sent * 100)) / (word)
Grade = round(0.0588 * L - 0.296 * S - 15.8)
if (Grade >= 16):
    print("Grade 16+")
elif (Grade < 1):
    print("Before Grade 1")
else:
    print(f"Grade {Grade}.")

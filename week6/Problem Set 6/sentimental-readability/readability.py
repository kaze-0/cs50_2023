from cs50 import get_string

def count_letters(text):
    ctrLett = 0
    for letter in text.lower():
        if ord(letter) in range(97, 122 + 1, 1): #ord(char)->ascii chr(ascii)->char
            ctrLett += 1
    return ctrLett

def count_words(text):
    ctrWord = 1
    for letter in text:
        if letter == ' ':
            ctrWord += 1
    return ctrWord

def count_sentences(text):
    ctrSent = 0
    for letter in text:
        if letter in ['.', '?', '!']:
            ctrSent += 1
    return ctrSent

text = get_string("Text: ")
l = count_letters(text)
w = count_words(text)
s = count_sentences(text)
r = 0.0588 * l / w * 100 - 0.296 * s / w * 100 - 15.8
#print(l, w, s, r)
if r < 1:
    print("Before Grade 1")
elif r > 16:
    print("Grade 16+")
else:
    print(f"Grade: {round(r)}")



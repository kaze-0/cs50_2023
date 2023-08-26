from sys import exit

from cs50 import get_string
cardStr = get_string("Number: ")
RcardStr = cardStr[::-1]
len = len(cardStr)



sum = 0
for n in range(1, len, 2):
    sum += int(RcardStr[n]) * 2 // 10 + int(RcardStr[n]) * 2 % 10
for n in range(0, len, 2):
    sum += int(RcardStr[n])
if sum % 10 != 0:
    print("INVALID")
    exit()

card = int(cardStr)
if len == 15 and (card // 1e13 == 34 or card // 1e13 == 37):
    print("AMEX")
elif len == 16 and ((card // 1e14) in [51, 52, 53, 54, 55]):
    print("MASTERCARD")
elif (len == 13 and card // 1e12 == 4) or (len == 16 and card // 1e15 == 4):
    print("VISA")
else:
    print("INVALID")


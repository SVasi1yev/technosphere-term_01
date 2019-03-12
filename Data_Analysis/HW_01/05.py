import sys

a = 0

for i in range(1, 11):
    print('? ' + str(i * 10000), flush=True)
print('+', flush=True)
s = 0
for i in range(1, 11):
    s += int(input())
if s == 0:
    print('! 100000', flush=True)
    sys.exit()

a = (10 - s) * 10000

for k in range(3, -1, -1):
    for i in range(1, 10):
        print('? ' + str(a + i * 10 ** k), flush=True)
    print('+', flush=True)
    s = 0
    for i in range(1, 10):
        s += int(input())

    a += (9 - s) * 10 ** k

print('! ' + str(a), flush=True)
n = int(input())
b = input()
a = b.split(' ')

i = 0
k = 0
while i < len(a):
    if a[:i].count(a[i]):
        k += 1
        a.pop(i)
    else:
        i += 1

print(' '.join(a))
print(k)
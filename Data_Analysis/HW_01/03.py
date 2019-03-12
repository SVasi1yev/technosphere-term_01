t = input()
n = int(t.split(' ')[0])
k = int(t.split(' ')[1])

a = []
for i in range(1, n - k + 3):
    a.append(str(2 - i % 2))
    
for i in range(3, k + 1):
    a.append(str(i))
    
print(' '.join(a))
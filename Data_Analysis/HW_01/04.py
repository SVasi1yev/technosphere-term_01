n = int(input())
k = int(input())

a = []

for i in range(k):
    t = input().split(' ')
    b = []
    b.append(int(t[0]))
    b.append(int(t[1]))
    a.append(b)
    
for i in range(len(a)):
    for j in range(i + 1, len(a)):
        if (a[j][0] <= a[i][0] <= a[j][1]) or (a[j][0] <= a[i][1] <= a[j][1]):
            k -= 1
            break;
            
print(str(k))
    
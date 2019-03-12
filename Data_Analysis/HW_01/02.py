def sort_key(input_str):
    s = 0
    for x in input_str:
        s += int(x)
    return s + int(input_str) * 0.00001

n = int(input())
b = input()
a = b.split(' ')
a.sort(key=sort_key)
print(' '.join(a))
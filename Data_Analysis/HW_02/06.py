def brackets1(n, counter_open = 0, counter_close = 0, ans = ''):
    if counter_open + counter_close == 2 * n:
        yield ans
    if counter_open < n:
        yield from brackets1(n, counter_open + 1, counter_close, ans + '(')
    if counter_open > counter_close:
        yield from brackets1(n, counter_open, counter_close + 1, ans + ')')
   
def brackets(n):
    yield from brackets1(n)

try:
    n = int(input())
    for e in brackets(n):
        print(e)
except:
    pass
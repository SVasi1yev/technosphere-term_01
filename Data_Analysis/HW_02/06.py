a = [1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796]

def brackets(n):
    i = 0
    if n == 1:
        yield '()'
    else:
        for e in brackets(n - 1):
            yield '(' + e + ')'
            i += 1
        for e in brackets(n - 1): 
            if (i >= a[n]):
                break
            yield e + '()'
            i += 1
            if (i >= a[n]):
                break
            yield '()' + e
            i += 1
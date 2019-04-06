import functools

def counter(func):
    first_call = [True, 0]
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        temp = False
        if first_call[0]:
            first_call[1] = 1
            wrapper.rdepth = 1
            wrapper.ncalls = 0
            first_call[0] = False
            temp = True
        wrapper.rdepth = max(first_call[1], wrapper.rdepth)
        first_call[1] += 1
        res = func(*args, **kwargs)
        first_call[1] -= 1
        wrapper.ncalls += 1
        if temp:
            first_call[0] = True
        return res
    return wrapper
import functools
import time

def timeout(rps):
    def decorator(func):
        a = [0, 0]
        @functools.wraps(func)
        def wrapper(*args, **kwargs):
            a[0] = time.time()
            res = func(*args, **kwargs)
            time.sleep(max(0, a[0] + 1 / rps - time.time()))
            return res
        return wrapper
    return decorator
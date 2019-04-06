import re
from functools import reduce
import operator

solutions = {
    'solution1': lambda arg : list(map(lambda x : int(reduce(lambda x, y : x + y, re.findall(r'\d', x))[::-1]), arg)),
    'solution2': lambda arg : list(map(lambda x : x[0] * x[1], arg)),
    'solution3': lambda arg : list(filter(lambda x : x % 6 == 0 or x % 6 == 2 or x % 6 == 5, arg)),
    'solution4': lambda arg : list(filter(None, arg)),
    'solution5': lambda arg : list(map(lambda x : operator.setitem(x, "square", x["length"] * x["width"]), arg)),
    'solution6': lambda arg : list(map(lambda x : dict(x, square = x["length"] * x["width"]), arg)),
    'solution7': lambda arg : reduce(operator.and_, arg),
    'solution8': lambda arg : reduce(lambda x, y: operator.setitem(x, y, x[y] + 1) or x, arg, dict(map(lambda x : (x, 0), arg))),
    'solution9': lambda arg : list(map(lambda x : x["name"], (filter(lambda x : x["gpa"] > 4.5, arg)))),
    'solution10': lambda arg : list(filter(lambda x : reduce(lambda z, x : z + int(x), x[::2], 0) \
                                         == reduce(lambda z, x : z + int(x), x[1::2], 0), arg)),
}
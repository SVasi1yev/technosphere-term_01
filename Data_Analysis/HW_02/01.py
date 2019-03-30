def solution1(arg):
    return [c * 4 for c in arg]

def solution2(arg):
    return [c * (i + 1) for i, c in enumerate(arg)]

def solution3(arg):
    return [i for i in arg if (i % 3 == 0 or i % 5 == 0)]

def solution4(arg):
    return [i for arr in arg for i in arr]

def solution5(arg):
    return [(a, b, c) for a in range(1, arg - 1) \
        for b in range(a + 1, arg) \
        for c in range(b + 1, arg + 1) \
        if (a ** 2 + b ** 2 == c ** 2)]

def solution6(arg):
    return [[j + i for j in arg[1]] for i in arg[0]]

def solution7(arg):
    return [[arg[i][j] for i in range(len(arg))] \
        for j in range(len(arg[0]))]

def solution8(arg):
    return [[int(c) for c in line.split(' ')] for line in arg]

def solution9(arg):
    return {chr(ord('a') + i) : i ** 2 for i in arg}

def solution10(arg):
    return {s.capitalize() for s in arg if len(s) > 3}

solutions = {
    'solution1': solution1,
    'solution2': solution2,
    'solution3': solution3,
    'solution4': solution4,
    'solution5': solution5,
    'solution6': solution6,
    'solution7': solution7,
    'solution8': solution8,
    'solution9': solution9,
    'solution10': solution10,
}
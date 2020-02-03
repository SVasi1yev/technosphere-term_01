solutions = {
    'solution1': lambda arg : [c * 4 for c in arg],
    'solution2': lambda arg : [c * (i + 1) for i, c in enumerate(arg)],
    'solution3': lambda arg : [i for i in arg if (i % 3 == 0 or i % 5 == 0)],
    'solution4': lambda arg : [i for arr in arg for i in arr],
    'solution5': lambda arg : [(a, b, c) for a in range(1, arg - 1) \
                                for b in range(a + 1, arg) \
                                for c in range(b + 1, arg + 1) \
                                if (a ** 2 + b ** 2 == c ** 2)],
    'solution6': lambda arg : [[j + i for j in arg[1]] for i in arg[0]],
    'solution7': lambda arg : [[arg[i][j] for i in range(len(arg))] \
                                for j in range(len(arg[0]))],
    'solution8': lambda arg : [[int(c) for c in line.split(' ')] for line in arg],
    'solution9': lambda arg : {chr(ord('a') + i) : i ** 2 for i in arg},
    'solution10': lambda arg : {s.capitalize() for s in arg if len(s) > 3},
}
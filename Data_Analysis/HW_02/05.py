def product(a):
    counts = [0 for i in range(len(a))]
    while(counts[0] < len(a[0])):
        yield tuple(a[i][j] for i, j in enumerate(counts))
        counts[-1] += 1
        for i in range(len(counts) - 1, 0, -1):
            if counts[i] == len(a[i]):
                counts[i] = 0
                counts[i - 1] += 1
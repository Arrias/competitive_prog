def sqrtEquality(a, b, c):
    ret = []
    d = b * b - 4 * a * c
    if d == 0:
        if ((-b)%(2*a)==0):
            ret.append((-b)//(2*a))
        return ret
    if (d < 0):
        return ret
    r = int(math.sqrt(d))
    while r * r < d:
        r += 1
    while r * r > d:
        r -= 1
    if (r * r != d):
        return ret
    if ((-b+r)%(2*a)==0):
        ret.append((-b+r)//(2*a))
    if ((-b-r)%(2*a)==0):
        ret.append((-b-r)//(2*a))
    return ret
from ast import literal_eval as eval
from functools import cmp_to_key

INPUT = "input.txt"
TEST = "test.txt"

def cmp(a: list, b: list):
    for p1, p2 in zip(a,b):
        if type(p1) is int and type(p2) is int:
            if p1 < p2:
                return -1
            if p1 == p2:
                continue
        elif type(p1) is int:
            c = cmp([p1], p2)
            if c == -1:
                return -1
            if c == 0:
                continue
        elif type(p2) is int:
            c = cmp(p1, [p2])
            if c == -1:
                return -1
            if c == 0:
                continue
        else:
            c = cmp(p1,p2)
            if c == -1:
                return -1
            if c == 0:
                continue
        return 1

    n = len(a)
    m = len(b)

    return (n > m) - (n < m)

def parse_list(l: list):
    res = []
    for e in l:
        if type(e) is int:
            res.append([e])
        else:
            res.append(parse_list(e))

    return res


def task1(input: str):
    with open(input, "r") as f:
        lines = f.readlines()

    pairs = []
    for i in range(0,len(lines),3):
        p1 = eval(lines[i])
        p2 = eval(lines[i+1])
        pairs.append((p1,p2))


    res = []
    for i, p in enumerate(pairs):
        p1,p2 = p
        if cmp(p1,p2) < 1:
            res.append(i+1)

    

    return res

    
       
def task2(input):
    with open(input, "r") as f:
        lines = f.readlines()

    packets = [[[2]], [[6]]]
    for i in range(0,len(lines),3):
        p1 = eval(lines[i])
        p2 = eval(lines[i+1])
        packets.append(p1)
        packets.append(p2)

    key = cmp_to_key(cmp)
    packets.sort(key=key)

    res = 1
    for i, p in enumerate(packets):
        if p == [[2]] or p == [[6]]:
            res *= i+1

    return res

print(sum(task1(TEST)))
print(sum(task1(INPUT)))
print(task2(TEST))
print(task2(INPUT))
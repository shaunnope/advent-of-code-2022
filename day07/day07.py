INPUT = "input.txt"
TEST = "test.txt"


def parse_line(line, path, dirs):
    tokens = line.split()
    if tokens[1] == "cd":
        if tokens[2] == "..":
            current = tuple(path)
            path.pop()
            dirs[tuple(path)] += dirs[current]
            pass
        else:
            path.append(tokens[2])
            dirs[tuple(path)] = 0

    elif tokens[0] not in ["$", "dir"]:
        dirs[tuple(path)] += int(tokens[0])

def parse_file(input):
    with open(input, "r") as f:
        lines = f.readlines()

    dirs = dict()
    path = []

    for line in lines:
        parse_line(line, path, dirs)

    return dirs
        

def task1(dirs):
    res = 0
    for size in dirs.values():
        if size <= 100000:
            res += size

    return res

def task2(dirs):
    sizes = sorted(list(dirs.values()))
    print(sizes)

    thres = sizes[-1] - 40000000

    for size in sizes:
        if size > thres:
            return size


dirs = parse_file(INPUT)
print(task1(dirs))
print(task2(dirs))
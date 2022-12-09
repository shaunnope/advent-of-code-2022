from math import prod

INPUT = "input.txt"
TEST = "test.txt"
       
def task2(input):
    with open(input, "r") as f:
        lines = f.readlines()

    grid = []

    for line in lines:
        grid.append(list(map(int, list(line[:-1]))))

    n = len(grid)
    m = len(grid[0])
    
    scores = [[[0,0,0,0] for _ in range(m)] for _ in range(n)]

    for i in range(1,n-1):
        for j in range(1,m-1):
            
            for a in range(i-1,-1,-1):
                scores[i][j][0] += 1
                if grid[i][j] <= grid[a][j]:
                    break

            for a in range(i+1,n):
                scores[i][j][1] += 1
                if grid[i][j] <= grid[a][j]:
                    break

            for a in range(j-1,-1,-1):
                scores[i][j][2] += 1
                if grid[i][j] <= grid[i][a]:
                    break

            for a in range(j+1,m):
                scores[i][j][3] += 1
                if grid[i][j] <= grid[i][a]:
                    break

    res = 0

    for i in range(1,n-1):
        for j in range(1,m-1):
            scores[i][j] = prod(scores[i][j])
            res = max(res, scores[i][j])

    return res

print(task2(INPUT))
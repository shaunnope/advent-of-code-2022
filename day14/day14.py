from copy import deepcopy
import sys
from sortedcontainers import SortedDict

INPUT = "input.txt"
TEST = "test.txt"

class Grid:
    grid: dict[int, SortedDict] = dict()
    flow = dict()
    lowest = 0
    grounded = False

    def __init__(self, grounded=False):
        self.grounded = grounded


    def __str__(self):
        rep = ""
        for i in range(self.lowest+2):
            for j in range(min(self.grid.keys())-1, max(self.grid.keys())+2):
                # if self.grid.get(j) is not None and len(self.grid.get(j)) == 1:
                #     continue
                c = self.get(j,i)
                if c is None:
                    c = "."
                rep += c
            
            rep += "\n"
            
        return rep

    def insert(self,x,y,a):
        if y > self.lowest:
            self.lowest = y

        if self.grid.get(x) is None:
            self.grid[x] = SortedDict()
        res = self.grid[x].setdefault(y,a)
        return res == a
    
    def get(self, x,y):
        if self.grid.get(x) is None:
            return None
        return self.grid[x].get(y)

    def find_below(self, x,y):
        if self.grid.get(x) is None or self.grid[x].peekitem()[0] < y:
            if not self.grounded:
                return None
            self.insert(x,self.lowest+2,"#")

        
        if self.grid[x].peekitem(0)[0] > y:
            return self.grid[x].peekitem(0)

        if self.insert(x,y,' '):
            ind = self.grid[x].index(y)+1
            res = self.grid[x].peekitem(ind)
            self.grid[x].pop(y)
            return res

        return y, self.grid[x].get(y)

    def find_free(self, x=500, y=-1):
        below = self.find_below(x,y)
        if below is None:
            return None
        if below[0] == y:
            return (x,y)

        y = below[0]-1
        free = None

        if self.get(x-1,y+1) and self.get(x+1,y+1): # solid ground
            return (x,y)

        if self.get(x-1,y+1) is None: # left empty
            free = self.find_free(x-1,y+1)
            if free != (x-1,y): # can drop left
                return free           
            
        if self.get(x+1,y+1) is None: # right empty
            right = self.find_free(x+1,y+1)
            if right != (x+1,y): # can drop right
                return right

        return (x,y)

    def find_free_prev(self, x=500, y=-1):
        below = self.find_below(x,y)
        if below[0] == y:
            return (x,y), None
        
        prev = None
        if below[0] - y >= 50:
            prev = (x,y-1)

        y = below[0]-1
        free = None

        if self.get(x-1,y+1) and self.get(x+1,y+1): # solid ground
            return (x,y), prev

        if self.get(x-1,y+1) is None: # left empty
            free = self.find_free(x-1,y+1)
            prev = (free[0]+1, free[1]-1)
            if free != (x-1,y): # can drop left
                return free, prev           
            
        if self.get(x+1,y+1) is None: # right empty
            right = self.find_free(x+1,y+1)
            rprev = (right[0]-1, right[1]-1)
            if right != (x+1,y): # can drop right
                return right, rprev

        return (x,y), prev

    def add_ground(self):
        lowest = self.lowest
        print(min(self.grid.keys())-20, max(self.grid.keys())+21)
        for i in range(min(self.grid.keys())-lowest, max(self.grid.keys())+lowest):
            self.insert(i,lowest+2, "#")

class Flow(Grid):
    # 0: up, 1: right, -1: left

    def __init__(self, grid:Grid, grounded=True):
        super().__init__(grounded)
        self.grid = deepcopy(grid.grid)
        self.state = grid

    def set_drop(self, x, y1, y2):
        for i in range(y1, y2+1):
            self.insert(x, i, 0)

    def find_free(self, x=500, y=-1):
        below = self.state.find_below(x,y)
        self.set_drop(x, y+1, below[0]-1)
        if below[0] == y:
            return (x,y)

        y = below[0]-1
        free = None

        if self.state.get(x-1,y+1) and self.state.get(x+1,y+1): # solid ground
            return (x,y)

        if self.state.get(x-1,y+1) is None: # left empty
            self.insert(x-1,y+1,1)
            free = self.find_free(x-1,y+1)
            if free != (x-1,y): # can drop left
                return free         
            
        if self.state.get(x+1,y+1) is None: # right empty
            self.insert(x+1,y+1,-1)
            right = self.find_free(x+1,y+1)
            if right != (x+1,y): # can drop right
                return right

        return (x,y)

    def backtrack(self, x,y):
        while self.state.get(x,y) is not None:
            if self.get(x,y) not in [0,1,-1]:
                return (500,-1)

            x += self.get(x,y)
            y -= 1

        return x,y


def parse_input(l: list[str], grounded=False):
    grid = Grid(grounded)
    for line in l:
        vertices = line.split("->")
        for i in range(len(vertices)-1):
            a,b = list(map(int, vertices[i].split(",")))
            x,y = list(map(int, vertices[i+1].split(",")))

            if a==x:
                for j in range(min(b,y), max(b,y)+1):
                    grid.insert(a,j,"#")
            else:
                for j in range(min(a,x), max(a,x)+1):
                    grid.insert(j,b,"#")

    if grounded:
        grid.add_ground()

    return grid


def task1(input: str):
    with open(input, "r") as f:
        lines = f.read().splitlines()

    grid = parse_input(lines)
    print(grid)

    res = 0
    free = grid.find_free()
    while free is not None:
        grid.insert(*free, "x")
        res += 1
        free = grid.find_free()  

    print(grid)
    return res

    
       
def task2(input):
    with open(input, "r") as f:
        lines = f.read().splitlines()

    grid = parse_input(lines, True)
    flow = Flow(grid) # 0: up, 1 right, -1: left
    print(grid)

    res = 0

    with open("out.txt", "w") as sys.stdout:
        free = flow.find_free()
        while free is not None:
            if grid.get(500,0) is not None:
                break
            grid.insert(*free, "x")
            res += 1
            prev = flow.backtrack(*free)
            free = flow.find_free(*prev)

        print(grid)
    sys.stdout = sys.__stdout__
    return res

# print(task1(TEST))
# print(task1(INPUT))
# print(task2(TEST))
print(task2(INPUT))

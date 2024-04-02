
INF = float('inf')

class Vertex():
    def __init__(self, idx) -> None:
        self.idx = idx
        self.dis = INF

    def isHPthan(self, vertex) -> bool:
        return self.dis < vertex.dis

    def printInfo(self):
        print('idx: {0}, dis: {1}'.format(self.idx, self.idx))

class Heap():
    def __init__(self, n) -> None:
        self.array = [ None for _ in range(n+1) ]
        self.size = n

    def deleteMin(self) -> int:
        data = self.array[1].idx
        self.array[1] = self.array[self.size]
        self.size -= 1
        self.percolateDown(1)
        return data

    def percolateDown(self, hole):
        tmp = self.array[hole]
        while (hole*2 <= self.size):
            child = hole*2
            if (child != self.size):
                if self.array[child+1].isHPthan(self.array[child]):
                    child += 1
            if (self.array[child].isHPthan(tmp)):
                self.array[hole] = self.array[child]
            else:
                break
            hole = child
        self.array[hole] = tmp

    def construct(self):
        for i in range(self.size//2, 0, -1):
            self.percolateDown(i)

class Graph():
    def __init__(self, n, m, k) -> None:
        self.n = n # n: node numbers
        self.m = m # m: edge numbers
        self.k = k # k: unit energy
        self.dis = [ INF for _ in range(n) ] # distance with initial value INF
        self.pre = [ None for _ in range(n) ] # pre-node with inital value None
        # 2D array with initalized weight INF or 0 
        self.weight = [ [ (INF if i != j else 0) for j in range(n) ] for i in range(n) ]
        # heap, saving the vertex
        self.heap = Heap(n)
        # an array to save all vetices
        self.vertex = [ Vertex(i) for i in range(n) ]
        self.heap.array = [None] + [ i for i in self.vertex]
        # set start point
        self.setDis(0, 0)

    # edge (u,v) with weight w
    def insert(self, u, v, w) -> None:
        self.weight[u-1][v-1] = w
        self.weight[v-1][u-1] = w

    # set for the distance
    def setDis(self, v, value):
        self.dis[v] = value
        self.vertex[v].dis = value
        self.heap.construct()
    
    def relaxing(self, u, v, w) -> None:
        if self.pre[u] != None and k != 0:
            new_w = self.weight[self.pre[u]][u] * self.k
            if (new_w < self.weight[self.pre[u]][v]):
                self.weight[self.pre[u]][v] = new_w
                w = int(w * (k-1) / k)
        if (self.dis[v] > self.dis[u] + w):
            self.setDis(v, self.dis[u] + w)
            self.pre[v] = u

    def specialShortestPath(self) -> list:
        while (self.heap.size != 0):
            u = self.heap.deleteMin()
            for v in range(self.n):
                w = self.weight[u][v]
                if w == INF:
                    continue
                else:
                    self.relaxing(u, v, w)
        return self.dis

    def printWeight(self):
        for i in self.weight:
            print(i)

if (__name__ == '__main__'):
    n, m, k = [ int(i) for i in input().split(' ') ]
    # solution class
    solution = Graph(n, m, k)
    # do the vertex insertion
    for _ in range(m):
        u ,v, w = [ int(i) for i in input().split(' ') ]
        solution.insert(u, v, w)
    ans_lst = solution.specialShortestPath()
    for i in ans_lst:
        print(i if i != INF else -1, end=' ')


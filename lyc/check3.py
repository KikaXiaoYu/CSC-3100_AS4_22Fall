from heapq import *
import math

class Graph1(): 
    def __init__(self,n):
        self.n = n
        self.edges = {}
        self.seen_edge = []
        self.seen_node = []
        self.dis_from_begin = []
        
    def draw(self,v,w,l):
        if (v in self.edges) is False:
            self.edges[v]={}
        if (w in self.edges) is False:
            self.edges[w]={}
        self.edges[v][w]=l
        self.edges[w][v]=l        

    def dij(self):
        for i in range(0,n):
            self.dis_from_begin.append(-1)
        self.dis_from_begin[0]=0        
        predecessor_for_each_nodes = {}
        pq = []
        heappush(pq,(0,'1'))
        while len(pq) != 0:
            x=heappop(pq)
            cur = x[1]
            if cur in self.seen_node:
                continue
            self.seen_node.append(cur)
            for i in self.edges[cur].keys():
                if i not in self.seen_node:
                    nei_edge = self.edges[cur][i]
                    before_i = self.dis_from_begin[int(i)-1]
                    if before_i == -1:
                        before_i = math.inf
                    dis_cur_begin = self.dis_from_begin[int(cur)-1]
                    if dis_cur_begin == -1:
                        dis_cur_begin = math.inf
                    now_i = dis_cur_begin+nei_edge
                    if before_i > now_i:
                        heappush(pq,(now_i,i))
                        self.dis_from_begin[int(i)-1]=now_i
                        predecessor_for_each_nodes[i]=cur
        # print(self.seen_node)
        return self.dis_from_begin

class Graph2():
    pass

if __name__ == '__main__':
    x = input().split()
    n = int(x[0])
    m = int(x[1])
    K = int(x[2])
    if K == 0:
        graph = Graph1(n)       
    else:
        graph = Graph2(n)
    for i in range(0,int(m)):
        y = input().split()
        v = y[0]
        w = y[1]
        l = int(y[2])
        graph.draw(v,w,l) 
    ans = graph.dij()
    print(*ans)

    

   

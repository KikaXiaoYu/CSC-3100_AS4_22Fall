
class FootBallMatch():
    def __init__(self, n, M, pop_lst) -> None:
        self.n = n
        self.m = M
        self.pop_lst = pop_lst

    def getAttr(self, a, b):
        return (a * b) % self.m
    
    def getEdgeLst(self):
        res_lst = []
        for i in range(len(self.pop_lst)):
            for j in range(i+1, len(self.pop_lst)):
                res_lst.append(self.getAttr(pop_lst[i], pop_lst[j]))

if (__name__ == '__main__'):
    n, M = [ int(i) for i in input().split(' ') ]
    pop_lst = [ int(i) for i in input().split(' ') ]

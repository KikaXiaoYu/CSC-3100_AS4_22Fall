
class MedianSearchTree():
    def __init__(self, n, k):
        self.n = n
        self.k = k
        self.bgheap = [ None for _ in range(k+n) ]
        self.smheap = [ None for _ in range(k+n) ]
        self.bgsize = 0
        self.smsize = 0
    
    def bgInsert(self, w):
        self.bgsize += 1
        hole = self.bgsize
        while ( hole > 1 and w > self.bgheap[hole//2] ):
            self.bgheap[hole] = self.bgheap[hole//2]
            hole //= 2
        self.bgheap[hole] = w

    def smInsert(self, w):
        self.smsize += 1
        hole = self.smsize
        while ( hole > 1 and w < self.smheap[hole//2] ):
            self.smheap[hole] = self.smheap[hole//2]
            hole //= 2
        self.smheap[hole] = w

    def bgDown(self, hole):
        tmp = self.bgheap[hole]
        while (hole*2 <= self.bgsize):
            child = hole*2
            if (child != self.bgsize and
                self.bgheap[child+1] > self.bgheap[child]): 
                    child += 1
            if (self.bgheap[child] > tmp):
                self.bgheap[hole] = self.bgheap[child]
            else:
                break
            hole = child
        self.bgheap[hole] = tmp

    def smDown(self, hole):
        tmp = self.smheap[hole]
        while (hole*2 <= self.smsize):
            child = hole*2
            if (child != self.smsize and
                self.smheap[child+1] < self.smheap[child]): 
                    child += 1
            if (self.smheap[child] < tmp):
                self.smheap[hole] = self.smheap[child]
            else:
                break
            hole = child
        self.smheap[hole] = tmp

    def bgPop(self):
        data = self.bgheap[1]
        self.bgheap[1] = self.bgheap[self.bgsize]
        self.bgheap[self.bgsize] = None
        self.bgsize -= 1
        self.bgDown(1)
        return data

    def smPop(self):
        data = self.smheap[1]
        self.smheap[1] = self.smheap[self.smsize]
        self.smheap[self.smsize] = None
        self.smsize -= 1
        self.smDown(1)
        return data

    def insert(self, w):
        self.bgInsert(w)
        self.smInsert(self.bgPop())
        if (self.bgsize < self.smsize):
            self.bgInsert(self.smPop())

    def outputMedian(self):
        output_lst = [ None for _ in range(2*self.k) ]
        new_tree = MedianSearchTree(0, self.k)
        new_tree.bgheap = self.bgheap.copy()
        new_tree.smheap = self.smheap.copy()
        new_tree.bgsize = self.bgsize
        new_tree.smsize = self.smsize
        for i in range(self.k):
            output_lst[self.k-i-1] = new_tree.bgPop()
        for i in range(self.k):
            output_lst[self.k+i] = new_tree.smPop()
        for i in output_lst:
            print(i, end=' ')
        print()

    def bgDelete(self, num):
        wait_lst = [ None for _ in range(num) ]
        for i in range(num):
            wait_lst[num-i-1] = self.bgPop()
        for i in range(1, num):
            self.bgInsert(wait_lst[i])
        if (self.bgsize < self.smsize):
            self.bgInsert(self.smPop())
    
    def smDelete(self, num):
        wait_lst = [ None for _ in range(num) ]
        for i in range(num):
            wait_lst[i] = self.smPop()
        for i in range(num-1):
            self.smInsert(wait_lst[i])
        if (self.bgsize - self.smsize == 2):
            self.smInsert(self.bgPop())
        
    def delete(self, p):
        if ( 1 <= p <= self.k ):
            self.bgDelete(self.k-p+1)
        if ( self.k+1 <= p <= 2*self.k):
            self.smDelete(p-self.k)

if (__name__ == '__main__'):
    n, k = [ int(i) for i in input().split(' ') ] 
    numbers = [ int(i) for i in input().split(' ') ]
    solution = MedianSearchTree(n, k)
    for i in numbers:
        solution.insert(i)
    for _ in range(n):
        line_lst = [ int(i) for i in input().split(' ') ]
        if (line_lst[0] == 1):
            solution.insert(line_lst[1])
        if (line_lst[0] == 2):
            solution.outputMedian()
        if (line_lst[0] == 3):
            solution.delete(line_lst[1])

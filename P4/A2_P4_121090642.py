
class Node():
    def __init__(self, value) -> None:
        self.value = value
        self.child_dic = {}
        self.sub_count = 0

class Prefix():
    def __init__(self) -> None:
        self.root = Node('')

    def getNum(self, prefix) -> int:
        cur_node = self.root
        for i in prefix:
            if (cur_node.child_dic.get(i) == None):
                return 0
            cur_node = cur_node.child_dic[i]
        return cur_node.sub_count
        
    def insert(self, str0) -> None:
        cur_node = self.root
        for i in range(len(str0)):
            if (cur_node.child_dic.get(str0[i]) == None):
                new_node = Node(str0[:i+1])
                cur_node.child_dic[str0[i]] = new_node
            cur_node = cur_node.child_dic[str0[i]]
            cur_node.sub_count += 1

if (__name__ == '__main__'):
    solution = Prefix()
    n = int(input())
    for _ in range(n):
        solution.insert(input())
    q = int(input())
    for _ in range(q):
        print(solution.getNum(input()))

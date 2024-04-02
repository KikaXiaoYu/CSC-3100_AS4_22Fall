from bisect import bisect_left,bisect_right
string1 = input()
ss = string1.split()
n = int(ss[0]) #n个节点
m = int(ss[1]) #m条边
k = int(ss[2]) #判断的倍数

#n= 10
#m = 30
#k = 1
#data =['10 7 35','7 4 77','1 3 35','9 2 33','2 4 4','5 9 2','4 1 60','7 3 30','7 9 99','3 7 31','8 4 63','7 10 71','7 5 45','10 3 41','6 8 62','6 1 98','3 5 36','10 3 93','7 3 63','6 8 27','2 4 53','6 7 38','4 8 62','7 2 20','2 1 63','5 7 78','1 9 30','2 8 91','10 4 10','4 6 66']
#data = ['4 6 38','3 6 14','5 1 92','7 5 100','10 3 65','1 4 37','3 9 77','7 8 79','10 3 11','7 5 69','8 4 29','1 6 13','9 2 5','9 5 31','7 3 41','8 9 82','5 4 17','9 5 51','6 3 72','8 7 27','7 5 84','2 6 10','7 3 3','9 2 16','9 4 21','3 4 7','4 1 16','1 5 17','5 8 69','5 6 22',]
#print('size of data:',len(data))

adjlist = []
for i in range(n + 1):
    adjlist.append([]) 
    #若不相邻，value是0

#读入数据集，建立原图，只需要单向
#for i in range(m):
#    string = data[i]
#    ls = string.split()
#    u = int(ls[0])
#    v = int(ls[1])
#    weight = int(ls[2])
#    adjlist[u].append([v,weight])

#读入数据集，建立原图，只需要单向
#print(0)
for i in range(m):
    string = input()
    ls = string.split()
    u = int(ls[0])
    v = int(ls[1])
    weight = int(ls[2])
    adjlist[u].append([v,weight])
#print(1)
#建立新图，构造中点，原图单向在新图变双向
new_adjlist = []
new_adjlist.append([]) #index = 0的位置不存储信息
for i in range(n):
    new_adjlist.append([]) 
for i in range(1,n+1):
    u = i
    for node_edge in adjlist[u]:
        v = node_edge[0]
        pev_weight = node_edge[1]
        #print('u:',u)
        #print('v:',v)
        mid_weight = pev_weight/2
        mid_node = len(new_adjlist)  #无需加1，因为new_adjlist的index=0没有用上,而且这是append之前的长度
        #print('mid_node: ',mid_node)
        new_adjlist[u].append([mid_node,mid_weight])
        new_adjlist[v].append([mid_node,mid_weight])
        new_adjlist.append([[u,mid_weight],[v,mid_weight]])
#print('new_adjlist',new_adjlist)

def position(element):
    return element[1]

def binary_use(weight_list,kw):
    left_index = bisect_left(weight_list,kw)
    right_index = bisect_right(weight_list,kw)
    return left_index,right_index


#判断新图的中点是否可以相连
#print('binary?')
for i in range(1,n+1): #第一层遍历是遍历原图中的vertex2
    if len(new_adjlist[i]) >= 2 : #最少有两个mid_node才可以形成小道
        origin_node = i
        length = len(new_adjlist[i])
        #print('len: ',length)
        adj_edges = new_adjlist[i] #这个list存储了所有跟原始图中一个点相邻的点和边
        adj_edges.sort(key=position) #根据weight大小排序
        weight_list = []
        for j in range(len(adj_edges)):
            weight_list.append(adj_edges[j][1])
        for m in range(len(adj_edges)):
            node_edge1 = adj_edges[m]
            node1 = node_edge1[0]
            weight1 = node_edge1[1]
            left_index,right_index = binary_use(weight_list,k*weight1)     #好像是左闭右开哦
            if left_index == len(weight_list): #说明没有这种倍数关系的邻边
                continue
            else:
                for y in range(left_index,right_index):
                    node_edge2 = adj_edges[y]
                    if node_edge1 == node_edge2:
                        continue
                    node2 = node_edge2[0]
                    weight2 = node_edge2[1]
                    new_weight = (k-1)*weight1
                    #这时,w2=k*w1
                    new_adjlist[node1].append([node2,new_weight])


# for i in range(len(new_adjlist)):
    # print(i, ': ',new_adjlist[i])

num_nodes = len(new_adjlist) - 1 #index为0的地方没有存储信息
d = []
p = []
d.append(-1)
p.append(None)
for i in range(1,num_nodes+1):
    d.append(-1)
    p.append('none')
d[1] = 0
#print('d : ', d) yes!

def heap_pop(heap):
    heap = heap[0:1] + heap[2:]
    return heap


def precolatedown(hole,arr):
    tmp = arr[hole]
    currentsize = len(arr) - 1
    while(hole*2 <= currentsize):
        child = hole*2
        if (child != currentsize and  ( arr[child+1][0] < arr[child][0]) ):
            child += 1
        if (arr[child][0] < tmp[0]):
            arr[hole] = arr[child]
        else:
            break
        hole = child
    arr[hole] = tmp
    return arr

def decrease_key(Q,key,new):
    Q[key] = new
    #print(Q[int(key/2)][0], ' ',Q[key][0])
    while key > 1 and (Q[int(key/2)][0]) >= (Q[key][0]):
        x1 = Q[key]
        x2 = Q[int(key/2)]
        Q[key] = x2
        Q[int(key/2)] = x1
        key = int(key/2)
    return Q

#print('new-adjlist: ', new_adjlist)
#for i in range(len(new_adjlist)):
    #print(i, ': ',new_adjlist[i])


#初始化 min-heap
Q = []
Q.append('NULL')     #只利用index:1～n
Q.append([0,1])      #index=0:distance, index=1:node
#print('begin1?')    yes!
#print('Q: ',Q)
#print('堆顶',Q[1]) 没有错
while Q != ['NULL'] : 
    node_weight = Q[1]   #获取堆顶元素
    #print(node_weight)
    u = node_weight[1]
    d_u = node_weight[0]
    #print('u: ', u)
    #print(0)
    if u != 1:           #无需考虑起点
        #print('yes1?')
        #print('u: ',u)
        if d[u] != -1:       
            #print('yes2?')
            if d_u > d[u]:      #heap里更新d,但是原来的没有被删去
                #print('yes3?')
                if  Q!= ['NULL']:    #删除栈顶元素
                    if len(Q) == 2:
                        #print(Q)
                        Q.pop() 
                        #print(Q)  
                    else:
                        Q[1] = Q[-1]
                        Q.pop()
                        Q = precolatedown(1,Q)
                        continue
    #print(u,' ',d[u])
    #print(1)
    if  Q!= ['NULL']:    #删除栈顶元素
        if len(Q) == 2:
            Q.pop()   
        else:
            Q[1] = Q[-1]
            Q.pop()
            Q = precolatedown(1,Q)
    #print('begin2?')
    connect = True      #记录判断是否存在连续三个mid_node的时候不能相连
    three_mid = False   #判断是不是三个连续mid_node
    for j in range(len(new_adjlist[u])):
        v = new_adjlist[u][j][0]
        w_uv = new_adjlist[u][j][1]
        #print('new_adjlist: ', new_adjlist)
        if p[u] != 'none':
            u_pre = p[u]
            if (u_pre > n):
                if u > n and v > n:  #只有是连续三个mid_node的时候才需要判断
                    for i in range(2):
                        x_node_edge = new_adjlist[u_pre][i]
                        #print('x_node_edge: ',x_node_edge)
                        x_node = x_node_edge[0]
                        for j in range(2):
                            y_node_edge = new_adjlist[v][j]
                            #print('y_node_edge: ',y_node_edge)
                            y_node = y_node_edge[0]
                            if (x_node == y_node)  and  (1 <= x_node <= n) :  #说明连续三个mid_node不能相连
                                connect = False
                                break
                        if connect == False:
                            break
                    if connect == False:
                        break
        if connect == True:            #不存在连续两条小道围绕同一个原始图的点，不一定是连续三个mid_node
            if d[v] != -1:                           #说明有关distance_v已经被添加进heap里面只需要改变其在heap中的位置，
                    if d[v] > d[u] + w_uv:
                        d[v] = d[u] + w_uv
                        p[v] = u
                        new = [d[v],v]
                        Q.append(new)
                        Q = decrease_key(Q,len(Q)-1,new)
            else:                                       #说明有关distance_v没有被添加进heap里面，先添加到堆底，再平衡
                    d[v] = float(d[u] + w_uv)
                    p[v] = u
                    new = [d[v],v]
                    Q.append(new)
                    key = len(Q) - 1
                    Q = decrease_key(Q,key,new)


for i in range(1,n+1):
    if d[i] == -1:
        print(-1, end=' ')
    else:
        print(int(d[i]), end=' ')
print()
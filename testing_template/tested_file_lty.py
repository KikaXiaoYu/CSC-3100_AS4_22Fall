import time
import heapq


def dijkstra(G,start):     ###dijkstra算法    
    INF = 999999999

    # dis = dict((key,INF) for key in G)    # start到每个点的距离
    dis = [INF for _ in range(len(G)+1)]
    dis[start] = 0  
    #{1:999999999,2:999999999,3:999999999,4:999999999}
    # vis = dict((key,False) for key in G)    #是否访问过，1位访问过，0为未访问
    #{1:false,2:false,3:false,4:false}
    vis = [False for _ in range(len(G)+1)]

    ###堆优化
    pq = []    #存放排序后的值
    # print([dis[start],start])
    heapq.heappush(pq,[dis[start],start])

    # t3 = time.time()
    # path = dict((key,[start]) for key in G)    #记录到每个点的路径
    #pq:[[0,1]]

    while len(pq)>0:
        v_dis,v = heapq.heappop(pq)    #未访问点中距离最小的点和对应的距离
        if vis[v] == True:
            continue
        vis[v] = True
        # p = path[v].copy()    #到v的最短路径
        for node in G[v]:   #与v直接相连的点
            # print(node)
            
            # temp = G[v][node][0]
            # for i in range(len(G[v][node])):
            #     if G[v][node][i] < temp:
            #         temp = G[v][node][i]

            # new_dis = dis[v] + float(temp)
            new_dis = dis[v] + float(G[v][node])

            if new_dis < dis[node] and (not vis[node]):    #如果与v直接相连的node通过v到src的距离小于dis中对应的node的值,则用小的值替换
                dis[node] = new_dis    #更新点的距离
                # dis_un[node][0] = new_dis    #更新未访问的点到start的距离
                heapq.heappush(pq,[dis[node],node])
                # print(pq)
                # temp = p.copy()
                # temp.append(node)    #更新node的路径
                # path[node] = temp    #将新路径赋值给temp

    # return dis,path
    # return dis
    for i in range(N):
        print(int(dis[i+1]) if dis[i+1] != 999999999 else -1, end=' ')
        # if dis[i+1] != 999999999:
        # else:
        #     print(-1 , end=' ')
    print()
    # t4 = time.time()
    # print('Dijkstra算法所用时间:',t4-t3)
    
def add_edge(G,y,K,n):
    # for i in G[y[0]]:
    #     if i == n+1:
    #         continue
    #     else:
    #         if y[2]/2/K == G[y[0]][i]:
    #             # print(n)
    #             # print(G)
    #             # print(i)
    #             G[i][n+1] = (K-1)/2*y[2]/K
    #         if y[2]/2*K == G[y[0]][i]:
    #             G[n+1][i] = (K-1)/2*y[2]
        
    # for i in G[y[1]]:
    #     if i == n+1:
    #         continue
    #     else:
    #         if y[2]/2/K == G[y[1]][i]:
    #             G[i][n+1] = (K-1)/2*y[2]/K
    #         if y[2]/2*K == G[y[1]][i]:
    #             G[n+1][i] = (K-1)/2*y[2]

    for i in G[y[1]]:

        if i == n+2:
            continue

        if y[2]/2/K == G[y[1]][i]:
            if First_line[0] % 2 == 1:
                if i % 2 == 0:
                    G[i+1][n+2] = (K-1)/2*y[2]/K
                else:
                    G[i-1][n+2] = (K-1)/2*y[2]/K
            else:
                if i % 2 == 1:
                    G[i+1][n+2] = (K-1)/2*y[2]/K
                else:
                    G[i-1][n+2] = (K-1)/2*y[2]/K

        if y[2]/2*K == G[y[1]][i]:
            # if First_line[0] % 2 == 1:
            #     if n % 2 == 0:
            #         G[i][n+1] = (K-1)/2*y[2]/K
            #     else:
            #         G[i-1][n+2] = (K-1)/2*y[2]/K
            # else:
            #     if i % 2 == 1:
            #         G[i+1][n+2] = (K-1)/2*y[2]/K
            #     else:
            #         G[i-1][n+2] = (K-1)/2*y[2]/K


            G[n+1][i] = (K-1)/2*y[2]

    for i in G[y[0]]:
        if i == n+1:
            continue

        if y[2]/2/K == G[y[0]][i]:
            if First_line[0] % 2 == 1:
                if i % 2 == 0:
                    G[i+1][n+1] = (K-1)/2*y[2]/K
                else:
                    G[i-1][n+1] = (K-1)/2*y[2]/K
            else:
                if i % 2 == 1:
                    G[i+1][n+1] = (K-1)/2*y[2]/K
                else:
                    G[i-1][n+1] = (K-1)/2*y[2]/K
            
        if y[2]/2*K == G[y[0]][i]:
            G[n+2][i] = (K-1)/2*y[2]


    # return G
    


if __name__ == '__main__':

    First_line = list(map(int, input().split()))

    # F = {}
    # for i in range(First_line[0]+First_line[1]):
    #     G[i+1] = {}
    #     G[i+1][i+1] = [0]
    # print(G)
    n = First_line[0]
    N = n
    w = First_line[1]
    K = First_line[2]
    G = []
    G = [ {} for _ in range(n+w*2+1)]
    # G.__sizeof__ = n+w*2+1
    # n = n + 1
    # for j in range(First_line[0]):
        # G[j+1] = {}
        # G[j+1][j+1] = 0
        # F[j+1] = {}
        # F[j+1][j+1] = 0

    for i in range(First_line[1]):
        y = list(map(int,input().split()))

        #建点建边
        # try:
        #     G[y[0]]
        # except:
        #     G[y[0]] = {}
        #     G[y[0]][y[0]] = 0
        
        # G[n+1] = {}
        G[n+1][n+1] = 0
        G[y[0]][n+1] = 0.5*y[2]
        G[n+1][y[1]] = 0.5*y[2]

        # G[n+2] = {}
        G[n+2][n+2] = 0
        G[y[1]][n+2] = 0.5*y[2]
        G[n+2][y[0]] = 0.5*y[2]

        # F[n+1] = {}
        # F[n+1][n+1] = 0
        # F[y[1]][n+1] = 0.5*y[2]
        # F[n+1][y[0]] = 0.5*y[2]

        # F[n+2] = {}
        # F[n+2][n+2] = 0
        # F[y[0]][n+2] = 0.5*y[2]
        # F[n+2][y[1]] = 0.5*y[2]



        if K != 0:
            add_edge(G, y,K,n)
        
        n = n+2

        
        

        # try:
        #     if G[y[0]][y[1]] < y[2]:
        #         pass
        #     else:
        #         G[y[0]][y[1]] = y[2]
        # except:
        #     G[y[0]][y[1]] = y[2]

        # try:
        #     if G[y[1]][y[0]] < y[2]:
        #         pass
        #     else:
        #         G[y[1]][y[0]] = y[2]   #可能会有错误，因为只算了最后一个
        # except:
        #     G[y[1]][y[0]] = y[2]  


    # print(G)

    # G = {1:{1:0, 2:10, 4:30, 5:100},
    #      2:{2:0, 3:50},
    #      3:{3:0, 5:10},
    #      4:{3:20, 4:0, 5:60},
    #      5:{5:0},
    #      }
    dijkstra(G,1)
    
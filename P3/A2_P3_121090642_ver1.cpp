
using namespace std;
#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<unordered_map>

class FootballMatch {
public:
    struct Edge {
        int u;
        int v;
        int w;
        bool operator < (const Edge & rhs) const {
            return (w > rhs.w);
        }
    };

    FootballMatch(int n, int m, vector<int> pop_lst):
        n(n), m(m) {
            initEdge(pop_lst);
        }

    void initEdge(vector<int> pop_lst) {
        for (int i = 0; i < n; i++) {
            for (int j = i; i < n; j++) {
                edge_queue.push({pop_lst[i], pop_lst[j], pop_lst[i]*pop_lst[j] % m});
            }
        }
    }

    void initSet() {
        for (int i = 0; i < n; i++) {
            label_map[i] = i;
            connected_map[i] = 0;
        }
    }

    void findMax() {
        int max_dis = 0;
        int node1;
        int node2;
        int weight;
        Edge edge;
        int node1_L;
        int node2_L;
        for (int i = 0; i < n*n/2; i++) {
            edge = edge_queue.top();
            edge_queue.pop();
            node1 = edge.u;
            node2 = edge.v;
            weight = edge.w;
            node1_L = label_map[node1];
            node2_L = label_map[node2];
            if (node1_L == node2_L) {
                continue;
            }
            if (connected_map[node1_L] >= connected_map[node2_L]) {
                
            }

        }
    }

    
    int n;
    int m;
    priority_queue<Edge> edge_queue;
    unordered_map<int, int> label_map;
    unordered_map<int, int> connected_map;

};




int main() {
    int n;
    int m;
    cin >> n >> m;
    vector<int> pop_lst;
    int pop_num;
    for (int i = 0; i < n; i++) {
        cin >> pop_num;
        pop_lst.push_back(pop_num);
    }
    
}
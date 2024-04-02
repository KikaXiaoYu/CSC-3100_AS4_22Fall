
using namespace std;
#include<iostream>
#include<string>
#include<vector>
#include<queue>

class Node {
public:
    Node(int idx0): idx(idx0) {
        color = __INT_MAX__; dis = __INT_MAX__; pre_node = nullptr; pre_dis = __INT_MAX__;
    }

    int idx;
    int color;
    int dis;
    Node* pre_node;
    int pre_dis;
    vector<Node*> neighbour_lst;
    vector<int> weight_lst; 
};

class Graph {
public:
    Graph(int n0, int m0, int k0): n(n0), m(m0), k(k0) { 
        initializeNodeLst();
    }

    void initializeNodeLst() {
        Node* node;
        for (int i = 0; i < n; i++) {
            node = new Node(i);
            node_lst.push_back(node);
        }
    }
    void insert(int u, int v, int w) {
        node_lst[u-1]->neighbour_lst.push_back(node_lst[v-1]);
        node_lst[u-1]->weight_lst.push_back(w);
        node_lst[v-1]->neighbour_lst.push_back(node_lst[u-1]);
        node_lst[v-1]->weight_lst.push_back(w);
    }

    void updateDis(int i, Node* cur_node, Node* next_node) {
        int new_weight = cur_node->weight_lst[i];
        int new_dis = cur_node->dis + new_weight;
        // cout << "new_weight: " << new_weight << endl;
        // cout << "new_dis: " << new_dis << endl;
        if (cur_node->weight_lst[i] == k * cur_node->pre_dis) {
            // cout << "cur_node->weight_lst[i] == k * cur_node->pre_dis" << endl;
            cur_node->pre_node->neighbour_lst.push_back(next_node);
            cur_node->pre_node->weight_lst.push_back(cur_node->weight_lst[i]);
            updateDis(cur_node->pre_node->neighbour_lst.size()-1, cur_node->pre_node, next_node);
            // cout << "special before new_weight: " << new_weight << endl;
            new_weight *= (float(k-1) / float(k));
            // cout << "special new_weight: " << new_weight << endl;
            new_dis = cur_node->dis + new_weight;
        }
        if (next_node->dis > new_dis) {
            next_node->dis = new_dis;
            // cout << "the dis for next_node is: " << next_node->dis << endl;
            next_node->pre_node = cur_node;
            next_node->pre_dis = new_weight;
            // cout << "the pre_dis is: " << next_node->pre_dis << endl;
        }
    }

    void specialShortestPath() {
        // initialize root
        node_lst[0]->color = 1;
        node_lst[0]->dis = 0;
        // initialize queue
        cur_queue.push(node_lst[0]);
        Node* cur_node;
        int cur_dis;
        queue<Node*> wait_lst;

        while (!cur_queue.empty()) {
            cur_node = cur_queue.front();
            // if (cur_node->color == 0) {
            //     for (int i = 0; i < wait_lst.size(); i++) {
            //         wait_lst.front()->color = -1;
            //         wait_lst.pop();
            //     }
            // }
            // cout << endl << "getNode: " << cur_node->idx + 1 << endl;
            cur_queue.pop();
            wait_lst.push(cur_node);
            cur_dis = cur_node->dis;
            for (int i = 0; i < cur_node->neighbour_lst.size(); i++) {
                if (cur_node->neighbour_lst[i]->color - cur_node->color >= 2) {
                    cur_node->neighbour_lst[i]->color = cur_node->color + 1;
                    cur_queue.push(cur_node->neighbour_lst[i]);
                }
                // if (cur_node->neighbour_lst[i]->color >= cur_node->color) {
                // cout << "updateDis: " << cur_node->idx+1 << " " << cur_node->neighbour_lst[i]->idx + 1 << endl;
                updateDis(i, cur_node, cur_node->neighbour_lst[i]);
                // }
            }
            
        }
        for (int i = 0; i < n; i++) {
            if (node_lst[i]->dis != __INT_MAX__) {
                cout << node_lst[i]->dis << " ";
            } else {
                cout << -1 << " ";
            }
        }
    }

    int n;
    int m;
    int k;
    vector<Node*> node_lst;
    queue<Node*> cur_queue;
};

int main() {
    int n;
    int m;
    int k;
    cin >> n >> m >> k;
    int u;
    int v;
    int w;
    Graph solution(n, m, k);
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        solution.insert(u, v, w);
    }
    solution.specialShortestPath();

}
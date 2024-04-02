
using namespace std;
#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<unordered_map>

class Node {
public:
    Node(int idx): idx(idx) {}
    bool operator < (const Node & rhs) const {
        return (key > rhs.key);
    }
    int idx;
    int key = __INT_MAX__;
    int pre = __INT_MAX__;
    bool exist = 1;
};

class FootballMatch {
public:
    
    FootballMatch(int n, int m, vector<int> pop_lst):
        n(n), m(m) {
            initQueue();
            cout << "t4" << endl;    
            initArray(pop_lst);
            cout << "t5" << endl;    
        }

    void initQueue() {
        Node* new_node;
        for (int i = 0; i < n; i++) {
            new_node = new Node(i);
            node_queue.push(new_node);
            node_lst.push_back(new_node);
        }
    }

    void insertEdge(int u, int v, int w) {
        weight_array[u-1][v-1] = w;
    }

    void initArray(vector<int> pop_lst) {
        int w;
        weight_array.resize(n);
        for (int i = 0; i <n; i++)
            weight_array[i].resize(n);
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                w = (pop_lst[i] * pop_lst[j]) % m;
                cout << "t6" << endl;
                weight_array[i][j] = w;
                weight_array[j][i] = w;
            }
        }
    }


    int prim() {
        int max = 0;
        node_lst[0] = 0;
        Node* u;
        cout << "testing1" << endl;
        while (!node_queue.empty()) {
            u = node_queue.top();
            node_queue.pop();
            cout << "t2" << endl;
            for (int v = 0; v < n; v++) {
                if (v != u->idx) {
                    cout << "t3" << endl;
                    cout << "u->idx: " << u->idx << endl;
                    cout << "v: " << v << endl;
                    cout << "weight_array[u->idx][v]: " << weight_array[u->idx][v] << endl;
                    cout << "node_lst[v]->key: " << node_lst[v]->key << endl;
                    if (node_lst[v]->exist == true && weight_array[u->idx][v] < node_lst[v]->key) {
                        cout << "t4" << endl;
                        node_lst[v]->pre = u->idx;
                        node_lst[v]->key = weight_array[u->idx][v];
                        max += node_lst[v]->key;
                    }
                    cout << "t5" << endl;
                }
            }
        }
        return max;
        
    }

    
    int n;
    int m;
    priority_queue<Node*> node_queue;
    vector<Node*> node_lst;
    vector<vector<int>> weight_array;


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
        cout << "testing2" << endl;
    }
    FootballMatch solution(n, m, pop_lst);
    cout << "testing3" << endl;
    cout << solution.prim();
}
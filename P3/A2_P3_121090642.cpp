
#include<iostream>
#include<vector>
using namespace std;

class FootballMatch
{
public:
    FootballMatch(long long int n, long long int m): num(n), module(m)
    {
        node_lst.resize(n);
        value_lst.resize(n);
        adj_matrix = vector<vector<long long int>>(n, vector<long long int>(n, INF));
        for (long long int i = 0; i < num; i++)
        {
            adj_matrix[i][i] = 0;
        }
    }

    void insertEdge(long long int u, long long int v, long long int w)
    {
        adj_matrix[u][v] = w;
        adj_matrix[v][u] = w;
    }

    void addNode(long long int cur_n, long long int value)
    {
        node_lst[cur_n] = cur_n;
        value_lst[cur_n] = value;
        long long int edge;
        for (long long int i = 0; i < cur_n; i++) {
            edge = (value_lst[i]*value_lst[cur_n]) % module;
            insertEdge(i, cur_n, edge);
        }
    }

    long long int prim(long long int start)
    {
        // int prim_res[num]; // the result of the MST's vertices
        long long int idx = 0; // for saving the prim_res usage
        long long int weights[num]; // the mininum weights from n to start
        // prim_res[idx++] = node_lst[start]; // save the start node
        long long int final_res = 0;

        // init the weights
        for (long long int i = 0; i < num; i++)
        {
            weights[i] = adj_matrix[start][i];
            // cout << "weights["<<i<<"] = mMatrix["<<start<<"]["<<i<<"] = " << weights[i] << endl;
        }
        weights[start] = 0;
        const long long int FLAG = 0;
        // for each node except start node
        for (long long int i = 0; i < num; i++)
        {
            if (start == i)
            {
                continue;
            }
            long long int max_node = 0; // the next min node
            long long int max = 0; // the minimun dis
            // find the min dis node
            for (long long int j = 0; j < num; j++) 
            {
                if (weights[j] != FLAG // not connected
                 && weights[j] > max) // smaller
                {
                    max = weights[j];
                    // cout << "node: " << i << endl;
                    // cout << "min = weights["<<j<<"] = "<< weights[j] << endl;
                    max_node = j;
                }
            }
            final_res += max;
            // track the found vertex
            // prim_res[idx++] = node_lst[max_node];
            // cout << "prim_res["<<idx<<"] = mVexs["<<max_node<<"] = "<< node_lst[max_node] << endl;
            // Flag the vertex as handled
            weights[max_node] = FLAG;

            // update the weights
            for (long long int j = 0; j < num; j++) {
                if (weights[j] != FLAG // not connected
                 && adj_matrix[max_node][j] > weights[j]) // smaller
                {
                    weights[j] = adj_matrix[max_node][j];
                }
            }
        }

        // for (int i = 0; i < num-1; i++)
        // {  
        //     cout << prim_res[i] << " ";
        // }
        // cout << endl;
        return final_res;
    }

    long long int num; // the number of nodes
    long long int module; // module
    vector<long long int> node_lst; // node set
    vector<long long int> value_lst; // node value set
    vector<vector<long long int>> adj_matrix; // Adjacent matrix
    const long long int INF = __INT64_MAX__; // maximun distance
    // 9223372036854775807
};


int main() {
    long long int n;
    long long int m;
    cin >> n >> m;
    FootballMatch solution(n, m);
    long long int pop_num;
    for (long long int i = 0; i < n; i++) {
        cin >> pop_num;
        solution.addNode(i, pop_num);
    }
    cout << solution.prim(0);
}

#include<iostream>
#include<vector>
using namespace std;

class MatrixUDG
{
public:
    MatrixUDG(int n): n(n)
    {
        mVexs.resize(n);
        for (int i = 0; i < n; i++)
        {
            mVexs[i] = i;
        }
        mMatrix = vector<vector<int>>(n, vector<int>(n, INF));
    }


    void insertEdge(int u, int v, int w)
    {
        mMatrix[u-1][v-1] = w;
        mMatrix[v-1][u-1] = w;
    }

    int prim(int start)
    {
        int prim_res[n]; // the result of the MST's vertices
        int idx = 0; // for saving the prim_res usage
        int weights[n]; // the mininum weights from n to start
        prim_res[idx++] = mVexs[start]; // save the start node
        int final_res = 0;

        // init the weights
        for (int i = 0; i < n; i++)
        {
            weights[i] = mMatrix[start][i];
            cout << "weights["<<i<<"] = mMatrix["<<start<<"]["<<i<<"] = " << weights[i] << endl;
        }
        weights[start] = 0;
        const int FLAG = 0;
        // for each node except start node
        for (int i = 0; i < n; i++)
        {
            if (start == i)
            {
                continue;
            }
            int min_node = 0; // the next min node
            int min = INF; // the minimun dis
            // find the min dis node
            for (int j = 0; j < n; j++) 
            {
                if (weights[j] != FLAG // not connected
                 && weights[j] < min) // smaller
                {
                    min = weights[j];
                    cout << "node: " << i << endl;
                    cout << "min = weights["<<j<<"] = "<< weights[j] << endl;
                    min_node = j;
                }
            }
            final_res += min;
            // track the found vertex
            prim_res[idx++] = mVexs[min_node];
            cout << "prim_res["<<idx<<"] = mVexs["<<min_node<<"] = "<< mVexs[min_node] << endl;
            // Flag the vertex as handled
            weights[min_node] = FLAG;

            // update the weights
            for (int j = 0; j < n; j++) {
                if (weights[j] != FLAG // not connected
                 && mMatrix[min_node][j] < weights[j]) // smaller
                {
                    weights[j] = mMatrix[min_node][j];
                }
            }
        }

        for (int i = 0; i < n-1; i++)
        {  
            cout << prim_res[i] << " ";
        }
        cout << endl;
        return final_res;
    }

    int n; // the number of vertices
    vector<int> mVexs; // vertices set
    vector<vector<int>> mMatrix; // Adjacent matrix
    const int INF = __INT_MAX__; // maximun distance
};

int main()
{
    int n;
    int e;
    int u;
    int v;
    int w;
    cin >> n >> e;
    MatrixUDG solution(n);
    for (int i = 0; i < e; i++)
    {
        cin >> u >> v >> w;
        cout << u << " "<< v << " " << w << endl;
        solution.insertEdge(u, v, w);
    }
    cout << solution.prim(0);
}
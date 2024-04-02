
#include <iostream>
#include <queue>
using namespace std;

typedef long double lldouble;
typedef long long int llint;

const lldouble INF = __DBL_MAX__;

struct Node {
	int idx;
	lldouble dis;
	bool operator < (const Node & rhs) const
	{
		return dis > rhs.dis;
	}
};

class SpecialShortestPath {
public:
	SpecialShortestPath(int n, int m, lldouble k): n(n), m(m), k(k)
	{
		neighbour_lst.resize(n+2*m);
		to_lst.resize(n+2*m);
		weight_lst.resize(n+2*m);
		dis_lst.resize(n+2*m);
		cur_edge = n-1;
		for (int i = 0; i < n+2*m; i++) {dis_lst[i] = INF;}
	}

	// a, b starts from 0
	void addsingleDirectEdge(int a, int b, lldouble w) {
		neighbour_lst[a].push_back(b);
		weight_lst[a].push_back(w);
	}

	void addSpecialEdge(lldouble w, int a, int size, int atob, int btoa) {
		for (int i = 0; i < size-1; i++)
		{
			if (w/2 == k*weight_lst[a][i])
			{
				int node = to_lst[a][i];
				addsingleDirectEdge(node, atob, (k-1)*w/2/k);
				// cout << "addsingleDirectEdge("<<node<< ' '<<node<<' '<<(k-1)*w/2/k<<")" << endl;
			}
			if (k*w/2 == weight_lst[a][i])
			{
				int node = neighbour_lst[a][i];
				addsingleDirectEdge(btoa, node, (k-1)*w/2);
				// cout << "addsingleDirectEdge("<<btoa<< ' '<<node<<' '<<(k-1)*w/2<<")" << endl;
			}
		}
	}

	// u, v starts from 0
	void insertGeneralEdge(int u, int v, lldouble w) {
		int utov = ++cur_edge;
		int vtou = ++cur_edge;

		addsingleDirectEdge(u, utov, w/2);
		addsingleDirectEdge(utov, v, w/2);
		addsingleDirectEdge(v, vtou, w/2);
		addsingleDirectEdge(vtou, u, w/2);

		to_lst[v].push_back(utov);
		// cout << "to_lst["<<v<<"].push_back("<<utov<<")"<<endl; 
		to_lst[u].push_back(vtou);
		// cout << "to_lst["<<u<<"].push_back("<<vtou<<")"<<endl; 

		int u_size = weight_lst[u].size();
		int v_size = weight_lst[v].size();

		addSpecialEdge(w, u, u_size, utov, vtou);
		addSpecialEdge(w, v, v_size, vtou, utov);
	}


	void dijkstra() {
		priority_queue<Node> heap; // heap

		bool vis[n+2*m];
		for (int i = 0; i < n+2*m; i++) {vis[i] = false;}
		dis_lst[0] = 0; // dis 1 to zero
		Node cur_node;
		cur_node.dis = 0;
		cur_node.idx = 0; // init
		heap.push(cur_node); // init heap first

		while(!heap.empty())
		{
			Node cur_node = heap.top();
			heap.pop();
			int u = cur_node.idx; // the idx of the node
			if (vis[u] == false) // not visited
			{
				for (int i = 0; i < neighbour_lst[u].size(); i++)
				{
					int v = neighbour_lst[u][i]; // neighbour node
					lldouble new_dis = weight_lst[u][i];

					if (dis_lst[v] > dis_lst[u] + new_dis)
					{ // weight smaller
						dis_lst[v] = dis_lst[u] + new_dis; // update
						cur_node.dis = dis_lst[v]; // set dis
						cur_node.idx = v; // set idx
						heap.push(cur_node); // push new node
					}
				}
				vis[u] = true;
			}
	
		}
		for (int i = 0; i < n; i++)
		{
			if (dis_lst[i] != INF)
			{
				cout << llint(dis_lst[i]) << ' ';
			} else {
				cout << -1 << ' ';
			}
		}
	}

	int n;
	int m;
	lldouble k;
	int cur_edge;
	vector<vector<int>> neighbour_lst;
	vector<vector<int>> to_lst;
	vector<vector<lldouble>> weight_lst;
	vector<lldouble> dis_lst;

};

int main() {
	int n, m;
	lldouble k;
	cin >> n >> m >> k;
	SpecialShortestPath solution(n, m, k);
	int u, v;
	lldouble w;
	for (int i = 0; i < m; i++)
	{
		cin >> u >> v >> w;
		solution.insertGeneralEdge(u-1, v-1, w);
	}
	solution.dijkstra();
}
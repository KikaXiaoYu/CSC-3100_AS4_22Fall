
#include <iostream>
#include <queue>
using namespace std;

typedef long long int llint;

const llint INF = __INT64_MAX__;

struct Node {
	llint idx;
	llint dis;
	bool operator < (const Node & rhs) const
	{
		return dis > rhs.dis;
	}
};

class SpecialShortestPath {
public:
	SpecialShortestPath(llint n, llint m, llint k): n(n), m(m), k(k)
	{
		edge_lst.resize(n);
		virtual_edge_lst.resize(n);
		weight_lst.resize(n);
		virtual_weight_lst.resize(n);
		dis_lst.resize(n);
		for (llint i = 0; i < n; i++) {dis_lst[i] = INF;}
	} 

	void dijkstra() {
		priority_queue<Node> heap; // heap

		bool vis[n];
		for (llint i = 0; i < n; i++) {vis[i] = false;}
		bool virtual_vis[n];
		for (llint i = 0; i < n; i++) {virtual_vis[i] = true;}
		llint pre_node[n];
		for (llint i = 0; i < n; i++) {pre_node[i] = -1;}
		llint pre_dis[n];
		llint virtual_pre_dis[n];
		dis_lst[0] = 0; // dis 1 to zero
		Node cur_node;
		cur_node.dis = 0, cur_node.idx = 0; // init
		heap.push(cur_node); // init heap first

		while(!heap.empty())
		{
			Node cur_node = heap.top();
			heap.pop();
			llint u = cur_node.idx; // the idx of the node
			// cout << "edge_lst[u].size()" << endl;
			if (vis[u] == false) // not visited
			{
				// cout << "if (vis[u] == false)" << endl;
				for (llint i = 0; i < edge_lst[u].size(); i++)
				{
					llint v = edge_lst[u][i]; // neighbour node
					// cout << "llint v = edge_lst["<<u<<"]["<<i<<"] = "<< v << endl;
					if (pre_node[u] != -1 && weight_lst[u][i] == k*pre_dis[u])
					{
						// cout << "if (pre_node[u] != -1 && weight_lst[u][i] == k*pre_dis[u]" << endl;
						llint pre = pre_node[u];
						// cout << "t1" << endl;
						virtual_vis[pre] = false;
						// cout << "t2" << endl;
						// cout << "pre" << pre << endl;
						virtual_edge_lst[pre].push_back(v);
						// cout << "t3" << endl;
						virtual_weight_lst[pre].push_back(weight_lst[u][i]);
						// cout << "t4" << endl;
						cur_node.dis = dis_lst[pre];
						cur_node.idx = pre;
						heap.push(cur_node);
						// cout << "end of &&" << endl;
					}
					if (dis_lst[v] > dis_lst[u] + weight_lst[u][i])
					{ // weight smaller
						// cout << "if (dis_lst[v] > dis_lst[u] + weight_lst[u][i])" << endl;
						dis_lst[v] = dis_lst[u] + weight_lst[u][i]; // update
						// cout << "dis_lst[v] = dis_lst[u] + weight_lst[u][i] = "<<dis_lst[v]<< endl;
						pre_node[v] = u; // pre node
						pre_dis[v] = weight_lst[u][i]; // pre dis
						cur_node.dis = dis_lst[v]; // set dis
						cur_node.idx = v; // set idx
						heap.push(cur_node); // push new node
					}
				}
			}
			if (virtual_vis[u] == false)
			{
				for (llint i = 0; i < virtual_edge_lst[u].size(); i++)
				{
					llint v = virtual_edge_lst[u][i]; // neighbour node

					if (dis_lst[v] > dis_lst[u] + virtual_weight_lst[u][i])
					{ // weight smaller
						dis_lst[v] = dis_lst[u] + virtual_weight_lst[u][i]; // update
						// cout << "dis_lst[v] = dis_lst[u] + weight_lst[u][i] = "<<dis_lst[v]<< endl;
						// pre_node[v] = u; // pre node
						pre_dis[v] = virtual_weight_lst[u][i]*(k-1)/k; // pre dis
						cur_node.dis = dis_lst[v]; // set dis
						cur_node.idx = v; // set idx
						heap.push(cur_node); // push new node
					}
				}
			}
			vis[u] = true;
			virtual_vis[u] = true;
		}
		for (llint i = 0; i < n; i++)
		{
			if (dis_lst[i] != INF)
			{
				cout << dis_lst[i] << ' ';
			} else {
				cout << -1 << ' ';
			}
		}
	}

	llint n;
	llint m;
	llint k;
	vector<vector<llint>> edge_lst;
	vector<vector<llint>> virtual_edge_lst;
	vector<vector<llint>> weight_lst;
	vector<vector<llint>> virtual_weight_lst;
	vector<llint> dis_lst;

};

int main() {
	llint n, m, k;
	cin >> n >> m >> k;
	SpecialShortestPath solution(n, m, k);
	llint u, v, w;
	for (llint i = 0; i < m; i++)
	{
		cin >> u >> v >> w;
		solution.edge_lst[u-1].push_back(v-1);
		solution.edge_lst[v-1].push_back(u-1);
		solution.weight_lst[u-1].push_back(w);
		solution.weight_lst[v-1].push_back(w);
	}
	solution.dijkstra();
}

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
			cout << "llint u = cur_node.idx = " << u << endl;
			if (vis[u] == false) // not visited
			{
				cout <<endl<< "if (vis["<<u<<"] == false)" << endl;
				for (llint i = 0; i < edge_lst[u].size(); i++)
				{
					llint v = edge_lst[u][i]; // neighbour node
					cout << "\tllint v = edge_lst["<<u<<"]["<<i<<"] = "<< v << endl;
					cout << "\tweight_lst["<<u<<"]["<<i<<"] = " <<weight_lst[u][i] << endl;
					cout << "\tk*pre_dis["<<u<<"] = "<< k*pre_dis[u] << endl;
					cout << "\tpre_node[u] = "<< pre_node[u]<<endl;
					if (pre_node[u] != -1 
					 && pre_node[u] != v
					 && weight_lst[u][i] == k*pre_dis[u])
					{
						cout << endl<<"\tif (pre_node["<<u<<"] != -1 && weight_lst["<<u<<"]["<<i<<"] == k*pre_dis["<<u<<"] == "<< weight_lst[u][i]<< endl;
						llint pre = pre_node[u];
						cout <<"\t\tllint pre = pre_node["<<u<<"] = "<<pre<<endl;
						virtual_vis[pre] = false;
						cout << "\t\tvirtual_vis["<<pre<<"] = false;" << endl;
						virtual_edge_lst[pre].push_back(v);
						cout<<"\t\tvirtual_edge_lst["<<pre<<"].push_back("<<v<<");"<<endl;
						virtual_weight_lst[pre].push_back(weight_lst[u][i]);
						cout<<"\t\tvirtual_weight_lst["<<pre<<"].push_back("<<weight_lst[u][i]<<");"<<endl;
						cur_node.dis = dis_lst[pre];
						cout<<"\t\tcur_node.dis = dis_lst["<<pre<<"] = "<<cur_node.dis<<endl;
						cur_node.idx = pre;
						cout<<"\t\tcur_node.idx = pre = "<<pre<<endl; 
						heap.push(cur_node);
						cout <<"\t\theap.push(cur_node);"<<endl;
					}
					if (pre_node[u] != -1) {
						cout << "k*weight_lst[pre_node[u]][u]" << k*weight_lst[pre_node[u]][u] <<endl;
					}
					if (pre_node[u] != -1 
					 && pre_node[u] != v
					 && weight_lst[u][i] == k*virtual_pre_dis[u])
					{
						cout << endl<<"\tif (pre_node["<<u<<"] != -1 && weight_lst["<<u<<"]["<<i<<"] == k*weight_lst[pre_node[u]]["<<u<<"] == "<< weight_lst[u][i]<< endl;
						llint pre = pre_node[u];
						cout <<"\t\tllint pre = pre_node["<<u<<"] = "<<pre<<endl;
						virtual_vis[pre] = false;
						cout << "\t\tvirtual_vis["<<pre<<"] = false;" << endl;
						virtual_edge_lst[pre].push_back(v);
						cout<<"\t\tvirtual_edge_lst["<<pre<<"].push_back("<<v<<");"<<endl;
						virtual_weight_lst[pre].push_back(weight_lst[u][i]);
						cout<<"\t\tvirtual_weight_lst["<<pre<<"].push_back("<<weight_lst[u][i]<<");"<<endl;
						cur_node.dis = dis_lst[pre];
						cout<<"\t\tcur_node.dis = dis_lst["<<pre<<"] = "<<cur_node.dis<<endl;
						cur_node.idx = pre;
						cout<<"\t\tcur_node.idx = pre = "<<pre<<endl; 
						heap.push(cur_node);
						cout <<"\t\theap.push(cur_node);"<<endl;
					}
					if (dis_lst[v] > dis_lst[u] + weight_lst[u][i])
					{ // weight smaller
						cout << endl<<"\tif (dis_lst["<<v<<"] > dis_lst["<<u<<"] + weight_lst["<<u<<"]["<<i<<"])" << endl;
						dis_lst[v] = dis_lst[u] + weight_lst[u][i]; // update
						cout << "\t\ttdis_lst["<<v<<"] = dis_lst["<<u<<"] + weight_lst["<<u<<"]["<<i<<"] = "<<dis_lst[v]<< endl;
						pre_node[v] = u; // pre node
						cout <<"\t\tpre_node["<<v<<"] = u = "<<u<<endl;
						pre_dis[v] = weight_lst[u][i]; // pre dis
						cout <<"\t\tpre_dis["<<v<<"] = weight_lst["<<u<<"]["<<i<<"];"<<endl;
						cur_node.dis = dis_lst[v]; // set dis
						cout <<"\t\tcur_node.dis = dis_lst["<<v<<"]";
						cur_node.idx = v; // set idx
						cout<<"\t\tcur_node.idx = v = "<<v<<endl; 
						heap.push(cur_node); // push new node
						cout <<"\t\theap.push(cur_node);"<<endl;
					}
				}
				vis[u] = true;
			}
			if (virtual_vis[u] == false)
			{
				cout <<endl<< "if (virtual_vis["<<u<<"] == false)" << endl;
				for (llint i = 0; i < virtual_edge_lst[u].size(); i++)
				{
					llint v = virtual_edge_lst[u][i]; // neighbour node
					cout << "\tllint v = virtual_edge_lst["<<u<<"]["<<i<<"] = "<< v << endl;
					if (dis_lst[v] > dis_lst[u] + virtual_weight_lst[u][i])
					{ // weight smaller
						cout << endl<<"\tif (dis_lst["<<v<<"] > dis_lst["<<u<<"] + virtual_weight_lst["<<u<<"]["<<i<<"])" << endl;
						dis_lst[v] = dis_lst[u] + virtual_weight_lst[u][i]; // update
						cout << "\t\tdis_lst["<<v<<"] = dis_lst["<<u<<"] + weight_lst["<<u<<"]["<<i<<"] = "<<dis_lst[v]<< endl;
						// pre_node[v] = u; // pre node
						virtual_pre_dis[v] = virtual_weight_lst[u][i]*(1.0/k); // pre dis
						cout<<"\t\tpre_dis["<<v<<"] = virtual_weight_lst["<<u<<"]["<<i<<"]*(1/k) = "<<virtual_pre_dis[v]<< endl;
						cur_node.dis = dis_lst[v]; // set dis
						cout <<"\t\tcur_node.dis = dis_lst["<<v<<"]";
						cur_node.idx = v; // set idx
						cout<<"\t\tcur_node.idx = v = "<<v<<endl; 
						heap.push(cur_node); // push new node
						cout <<"\t\theap.push(cur_node);"<<endl;
					}
				}
				virtual_vis[u] = true;
			}
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
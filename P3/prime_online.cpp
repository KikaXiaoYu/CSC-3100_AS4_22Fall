
#include<iostream>
using namespace std;

const int MaxSize = 20;
const int INF = 2147483647;

int visited[MaxSize];
int lowcost[MaxSize];
int adjvex[MaxSize];

int MinEdge(int a[], int n) {
	int min = INF;
	int k = 0;
	for (int i = 1; i <= n; ++i)
	{
		if (min > a[i] && a[i] != 0)
		{
			min = a[i];
			k = i;
		}
	}
	return k;
}

class MGraph {
private:
	int weight_array[MaxSize][MaxSize];
	int vertex[MaxSize];
	int edge_num;
	int vertexNum;

public:
	MGraph(int a[], int n, int e) {
		edge_num = e;
		vertexNum = n;
		for (int i = 1; i <= vertexNum; ++i)
		{
			vertex[i] = a[i];
		}
		for (int i = 1; i <= vertexNum; ++i)
		{
			for (int j = 1; j <= vertexNum; ++j)
			{
				weight_array[i][j] = INF;
			}
		}
		for (int i = 1; i <= edge_num; ++i)
		{
			int a, b, v;
			cin >> a >> b >> v;
			weight_array[a][b] = weight_array[b][a] = v;
		}
	}

	void Prime() {
		for (int i = 2; i <= vertexNum; ++i) {
			lowcost[i] = weight_array[1][i];
			adjvex[i] = 1;
		}
		lowcost[1] = 0;
		for (int i = 2; i <= vertexNum; ++i) {
			int k = MinEdge(lowcost, vertexNum);
			cout << k << "  " << adjvex[k] << "  " << lowcost[k] << endl;
			lowcost[k] = 0;
			for (int j = 1; j <= vertexNum; ++j) {
				if (weight_array[k][j] < lowcost[j]) {
					lowcost[j] = weight_array[k][j];
					adjvex[j] = k;
				}
			}
		}
	}
};

int main()
{
	int a[MaxSize];
	for (int i = 1; i < MaxSize; ++i)
	{
		a[i] = i;
	}
	int x, y;
	cin >> x >> y;
	MGraph G(a, x, y);
	G.Prime();
	return 0;
}
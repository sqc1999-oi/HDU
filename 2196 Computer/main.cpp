#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
vector<int> G[10001];
int p[10001], Max[10001][2], Pos[10001], f[10001];

void pre_dfs(int u)
{
	Max[u][0] = 0;
	for (int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i];
		pre_dfs(v);
		if (Max[v][0] + p[v] > Max[u][0])
		{
			Max[u][0] = Max[v][0] + p[v];
			Pos[u] = v;
		}
	}
	Max[u][1] = 0;
	for (int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i];
		if (v != Pos[u] && Max[v][0] + p[v] > Max[u][1]) Max[u][1] = Max[v][0] + p[v];
	}
}

void dfs(int u)
{
	for (int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i];
		f[v] = max(f[u], Max[u][v == Pos[u] ? 1 : 0]) + p[v];
		dfs(v);
	}
}

int main()
{
	ios::sync_with_stdio(false);
	int n;
	while (cin >> n)
	{
		for (int i = 1; i <= n; i++) G[i].clear();
		for (int i = 2; i <= n; i++)
		{
			int a;
			cin >> a >> p[i];
			G[a].push_back(i);
		}
		pre_dfs(1);
		f[1] = 0;
		dfs(1);
		for (int i = 1; i <= n; i++) cout << max(f[i], max(Max[i][0], Max[i][1])) << endl;
	}
}

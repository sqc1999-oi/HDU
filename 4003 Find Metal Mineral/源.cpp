#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
struct Edge { int To, Pow; };
vector<Edge> G[10001];
int f[10001][11], p[10001];
void dfs(int u, int fa, int k)
{
	for (int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i].To, w = G[u][i].Pow;
		if (v != fa)
		{
			dfs(v, u, k);
			for (int j = k; j >= 0; j--)
			{
				f[u][j] += f[v][0] + 2 * w;
				for (int l = 1; l <= j; l++) f[u][j] = min(f[u][j], f[u][j - l] + f[v][l] + l * w);
			}
		}
	}
}
int main()
{
	ios::sync_with_stdio(false);
	int n, s, k;
	while (cin >> n >> s >> k)
	{
		memset(f, 0, sizeof f);
		for (int i = 1; i <= n; i++) G[i].clear();
		for (int i = 1; i < n; i++)
		{
			int a, b, c;
			cin >> a >> b >> c;
			G[a].push_back(Edge{ b,c });
			G[b].push_back(Edge{ a,c });
		}
		dfs(s, 0, k);
		cout << f[s][k] << endl;
	}
}

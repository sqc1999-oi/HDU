#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cstring>
#pragma comment(linker, "/STACK:1024000000,1024000000")
using namespace std;

struct Edge
{
	int To, Pow;
};

int D[40001], P[40001], f[40001][17];
vector<Edge> G[40001];

void dfs(int u, int fa, int d, int p)
{
	D[u] = d;
	P[u] = p;
	f[u][0] = fa;
	int lg = log2(d);
	for (int i = 1; i <= lg; i++)
		f[u][i] = f[f[u][i - 1]][i - 1];
	for (int i = 0; i < G[u].size(); i++)
		if (G[u][i].To != fa) dfs(G[u][i].To, u, d + 1, p + G[u][i].Pow);
}

int main()
{
	ios::sync_with_stdio(false);
	int t;
	cin >> t;
	while (t--)
	{
		int n, m;
		cin >> n >> m;
		for (int i = 1; i <= n; i++)
			G[i].clear();
		for (int i = 1; i < n; i++)
		{
			int a, b, c;
			cin >> a >> b >> c;
			G[a].push_back(Edge{b, c});
			G[b].push_back(Edge{a, c});
		}
		dfs(1, 0, 0, 0);
		for (int i = 1; i <= m; i++)
		{
			int a, b;
			cin >> a >> b;
			int x = a, y = b;
			if (D[a] > D[b]) swap(a, b);
			int lg = log2(D[b] - D[a]);
			for (int i = lg; i >= 0; i--)
			{
				if (D[b] - (1 << i) < D[a]) continue;
				if (D[a] == D[b]) break;
				b = f[b][i];
			}
			if (a == b)
			{
				cout << abs(P[x] - P[y]) << endl;
				continue;
			}
			lg = log2(D[a]);
			for (int i = lg; i >= 0; i--)
			{
				if (f[a][i] == f[b][i]) continue;
				a = f[a][i];
				b = f[b][i];
			}
			a = f[a][0];
			cout << P[x] + P[y] - 2 * P[a] << endl;
		}
	}
}

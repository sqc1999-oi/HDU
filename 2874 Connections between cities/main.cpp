#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
struct Query
{
	int u, v, lca;
} q[1000001];
struct Edge
{
	int To, Pow;
};
vector<Edge> G[10001];
vector<int> Q[10001];
int p[10001], d[10001], r[10001];
bool vis[10001];
int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
void tarjan_lca(int u, int fa, int root)
{
	r[u] = root;
	p[u] = u;
	vis[u] = true;
	for (int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i].To;
		if (v != fa)
		{
			d[v] = d[u] + G[u][i].Pow;
			tarjan_lca(v, u, root);
			p[v] = u;
		}
	}
	for (int i = 0; i < Q[u].size(); i++)
	{
		Query &cu = q[Q[u][i]];
		int v = cu.u == u ? cu.v : cu.u;
		if (vis[v] && r[u] == r[v])
			cu.lca = find(v);
	}
}
int main()
{
	ios::sync_with_stdio(false);
	int n, m, c;
	while (cin >> n >> m >> c)
	{
		for (int i = 1; i <= n; i++) G[i].clear(), Q[i].clear();
		memset(vis, 0x00, sizeof vis);
		for (int i = 1; i <= m; i++)
		{
			int a, b, c;
			cin >> a >> b >> c;
			G[a].push_back(Edge{ b,c });
			G[b].push_back(Edge{ a,c });
		}
		for (int i = 1; i <= c; i++)
		{
			cin >> q[i].u >> q[i].v;
			q[i].lca = 0;
			Q[q[i].u].push_back(i);
			Q[q[i].v].push_back(i);
		}
		for (int i = 1; i <= n; i++)
			if (!vis[i])
			{
				d[i] = 0;
				tarjan_lca(i, 0, i);
			}
		for (int i = 1; i <= c; i++)
		{
			if (q[i].lca == 0) cout << "Not connected" << endl;
			else cout << d[q[i].u] + d[q[i].v] - 2 * d[q[i].lca] << endl;
		}
	}
}

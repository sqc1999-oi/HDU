#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <cstring>
using namespace std;

struct Query
{
	int u, v, lca;
} q[100001];

vector<int> G[100001], Q[100001];
map<string, int> Map;
int p[100001], in[100001], d[100001];
bool vis[100001];

int find(int x)
{
	return x == p[x] ? x : p[x] = find(p[x]);
}

void tarjan_lca(int u)
{
	p[u] = u;
	vis[u] = true;
	for (int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i];
		d[v] = d[u] + 1;
		tarjan_lca(v);
		p[v] = u;
	}
	for (int i = 0; i < Q[u].size(); i++)
	{
		Query& cu = q[Q[u][i]];
		int v = cu.u == u ? cu.v : cu.u;
		if (vis[v])
			cu.lca = find(v);
	}
}

int main()
{
	ios::sync_with_stdio(false);
	int t;
	cin >> t;
	while (t--)
	{
		int n, m, cnt = 0;
		cin >> n >> m;
		for (int i = 1; i <= n; i++) G[i].clear() , Q[i].clear();
		Map.clear();
		memset(in, 0x00, sizeof in);
		memset(vis, 0x00, sizeof vis);
		for (int i = 1; i < n; i++)
		{
			string a, b;
			cin >> a >> b;
			if (!Map[a]) Map[a] = ++cnt;
			if (!Map[b]) Map[b] = ++cnt;
			G[Map[b]].push_back(Map[a]);
			in[Map[a]]++;
		}
		for (int i = 1; i <= m; i++)
		{
			string a, b;
			cin >> a >> b;
			q[i].u = Map[a];
			q[i].v = Map[b];
			q[i].lca = 0;
			Q[q[i].u].push_back(i);
			Q[q[i].v].push_back(i);
		}
		int root = 0;
		for (int i = 1; i <= n; i++)
			if (in[i] == 0)
			{
				root = i;
				break;
			}
		d[root] = 0;
		tarjan_lca(root);
		for (int i = 1; i <= m; i++)
		{
			int ans = d[q[i].u] - d[q[i].lca] + 1;
			if (q[i].v == q[i].lca) ans--;
			cout << ans << endl;
		}
	}
}
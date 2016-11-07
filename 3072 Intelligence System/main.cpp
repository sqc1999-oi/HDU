#include <iostream>
#include <algorithm>
#include <stack>
#include <vector>
#include <cstring>
using namespace std;
struct Edge { int From, To, Pow; } E[100001];
int dfn[50000], low[50000], index, com[50000], cnt, cost[50000];
bool vis[50000], ins[50000];
stack<int> s;
vector<int> G[50000];
void tarjan(int u)
{
	dfn[u] = low[u] = ++index;
	s.push(u);
	ins[u] = vis[u] = true;
	for (int i = 0; i < G[u].size();i++)
	{
		int v = G[u][i];
		if (!vis[v])
		{
			tarjan(v);
			low[u] = min(low[u], low[v]);
		}
		else if (ins[v]) low[u] = min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u])
	{
		int v;
		cnt++;
		do
		{
			v = s.top();
			s.pop();
			ins[v] = false;
			com[v] = cnt;
		}
		while (u != v);
	}
}
int main()
{
	ios::sync_with_stdio(false);
	int n, m;
	while (cin >> n >> m)
	{
		memset(vis, 0x00, sizeof vis);
		memset(cost, 0x7f, sizeof cost);
		for (int i = 0; i < n; i++) G[i].clear();
		index = cnt = 0;
		for (int i = 1; i <= m; i++)
		{
			cin >> E[i].From >> E[i].To >> E[i].Pow;
			G[E[i].From].push_back(E[i].To);
		}
		for (int i = 0; i < n; i++)
			if (!vis[i])
				tarjan(i);
		for (int i = 1; i <= m; i++)
			if (com[E[i].From] != com[E[i].To])
				cost[com[E[i].To]] = min(cost[com[E[i].To]], E[i].Pow);
		int ans = 0;
		for (int i = 1; i <= cnt; i++)
			if (cost[i] != 0x7f7f7f7f)
				ans += cost[i];
		cout << ans << endl;
	}
}

#include <iostream>
#include <algorithm>
#include <stack>
#include <vector>
#include <cstring>
using namespace std;

struct
{
	int From, To;
} e[10001];

int dfn[1001], low[1001], a[1001], com[1001], p[1001], in[1001], index, Cnt;
bool vis[1001], ins[1001];
vector<int> G[1001];
stack<int> s;

void tarjan(int u)
{
	vis[u] = ins[u] = true;
	dfn[u] = low[u] = ++index;
	s.push(u);
	for (int i = 0; i < G[u].size(); i++)
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
		int v, m = 0x7fffffff;
		Cnt++;
		do
		{
			v = s.top();
			s.pop();
			ins[v] = false;
			com[v] = Cnt;
			m = min(m, a[v]);
		}
		while (u != v);
		p[Cnt] = m;
	}
}

int main()
{
	ios::sync_with_stdio(false);
	int n, m;
	while (cin >> n >> m)
	{
		if (n == 0 && m == 0) break;
		for (int i = 1; i <= n; i++) G[i].clear();
		index = Cnt = 0;
		memset(vis, 0, sizeof vis);
		memset(in, 0, sizeof in);
		for (int i = 1; i <= n; i++) cin >> a[i];
		for (int i = 1; i <= m; i++)
		{
			cin >> e[i].From >> e[i].To;
			G[e[i].From].push_back(e[i].To);
		}
		for (int i = 1; i <= n; i++) if (!vis[i]) tarjan(i);
		for (int i = 1; i <= m; i++) if (com[e[i].From] != com[e[i].To]) in[com[e[i].To]]++;
		int ans = 0, cnt = 0;
		for (int i = 1; i <= Cnt; i++) if (in[i] == 0) ans += p[i] , cnt++;
		cout << cnt << ' ' << ans << endl;
	}
}

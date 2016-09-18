#include <iostream>
#include <algorithm>
#include <stack>
#include <vector>
#include <cstring>
using namespace std;
int dfn[10001], low[10001], index, cnt;
bool vis[10001], ins[10001];
vector<int> G[10001];
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
		else if (ins[u]) low[u] = min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u])
	{
		cnt++;
		while (u != s.top())
		{
			ins[s.top()] = false;
			s.pop();
		}
		ins[s.top()] = false;
		s.pop();
	}
}

int main()
{
	ios::sync_with_stdio(false);
	int n, m;
	while (cin >> n >> m)
	{
		if (n == 0 && m == 0) break;
		for (int i = 1; i <= n; i++)
			G[i].clear();
		index = cnt = 0;
		memset(vis, 0, sizeof vis);
		for (int i = 1; i <= m; i++)
		{
			int a, b;
			cin >> a >> b;
			G[a].push_back(b);
		}
		for (int i = 1; i <= n; i++)
			if (!vis[i]) tarjan(i);
		cout << (cnt == 1 ? "Yes" : "No") << endl;
	}
}

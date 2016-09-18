#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
vector<int> G[100001];
int pos, ans;

void dfs(int u, int fa, int d)
{
	if (d > ans)
	{
		ans = d;
		pos = u;
	}
	for (int i = 0; i < G[u].size(); i++)
		if (G[u][i] != fa) dfs(G[u][i], u, d + 1);
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
			int a, b;
			cin >> a >> b;
			G[a].push_back(b);
			G[b].push_back(a);
		}
		ans = 0;
		dfs(1, 0, 0);
		ans = 0;
		dfs(pos, 0, 0);
		ans++;
		for (int i = 1; i <= m; i++)
		{
			int x;
			cin >> x;
			if (x <= ans) cout << x - 1 << endl;
			else cout << ans - 1 + (x - ans) * 2 << endl;
		}
	}
}

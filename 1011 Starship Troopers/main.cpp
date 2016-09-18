#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cmath>
using namespace std;
vector<int> G[101];
int cost[101], val[101], f[101][101], n, m;

void dfs(int u, int fa)
{
	f[u][cost[u]] = val[u];
	for (int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i];
		if (v != fa)
		{
			dfs(v, u);
			for (int j = m; j >= 0; j--)
			{
				if (f[u][j] == -1) continue;
				for (int k = 0; k + j <= m; k++)
				{
					if (f[v][k] == -1) continue;
					f[u][j + k] = max(f[u][j + k], f[u][j] + f[v][k]);
				}
			}
		}
	}
	f[u][0] = 0;
}

int main()
{
	ios::sync_with_stdio(false);
	while (cin >> n >> m && !(n == -1 && m == -1))
	{
		for (int i = 1; i <= n; i++) G[i].clear();
		for (int i = 1; i <= n; i++)
		{
			cin >> cost[i] >> val[i];
			cost[i] = ceil(cost[i] / 20.0);
		}
		for (int i = 1; i < n; i++)
		{
			int a, b;
			cin >> a >> b;
			G[a].push_back(b);
			G[b].push_back(a);
		}
		memset(f, 0xff, sizeof f);
		dfs(1, 0);
		int ans = 0;
		for (int i = 0; i <= m; i++) ans = max(ans, f[1][i]);
		cout << ans << endl;
	}
}

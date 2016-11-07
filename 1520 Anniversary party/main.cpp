#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
int r[6001], in[6001];
vector<int> G[6001];
int dfs(int u,bool flag)
{
	int ans[2] = { 0,r[u] };
	for (int i = 0; i < G[u].size();i++)
	{
		ans[0] += dfs(G[u][i], false);
		if (!flag) ans[1] += dfs(G[u][i], true);
	}
	if (flag) return ans[0];
	return max(ans[0], ans[1]);
}
int main()
{
	ios::sync_with_stdio(false);
	int n;
	while (cin >> n)
	{
		memset(in, 0, sizeof in);
		for (int i = 1; i <= n; i++) G[i].clear();
		for (int i = 1; i <= n; i++) cin >> r[i];
		int l, k;
		while (cin >> l >> k)
		{
			if (l == 0 && k == 0) break;
			in[l]++;
			G[k].push_back(l);
		}
		int root = 0;
		for (int i = 1; i <= n; i++) if (in[i] == 0) root = i;
		cout << dfs(root, false) << endl;
	}
}

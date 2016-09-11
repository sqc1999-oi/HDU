#include <iostream>
#include <algorithm>
using namespace std;

struct edge
{
	int u, v, w;

	bool operator <(const edge &b) const
	{
		return w < b.w;
	}
} e[100001];

int p[101];

int find(int x)
{
	return x == p[x] ? x : p[x] = find(p[x]);
}

int main()
{
	ios::sync_with_stdio(false);
	int n, m;
	while (cin >> n >> m)
	{
		if (n == 0) break;
		for (int i = 1; i <= n; i++)
			cin >> e[i].u >> e[i].v >> e[i].w;
		sort(e + 1, e + 1 + n);
		for (int i = 1; i <= m; i++)
			p[i] = i;
		int cnt = 0, ans = 0;
		for (int i = 1; i <= n; i++)
		{
			int x = find(e[i].u), y = find(e[i].v);
			if (x != y)
			{
				cnt++;
				p[x] = y;
				ans += e[i].w;
			}
		}
		if (cnt < m - 1) cout << '?';
		else cout << ans;
		cout << endl;
	}
}

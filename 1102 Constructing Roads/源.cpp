#include <iostream>
#include <algorithm>
using namespace std;
int p[101];

struct edge
{
	int u, v, w;

	bool operator <(const edge &b) const
	{
		return w < b.w;
	}
} e[20001];

int find(int x)
{
	return x == p[x] ? x : p[x] = find(p[x]);
}

int main()
{
	ios::sync_with_stdio(false);
	int n;
	while (cin >> n)
	{
		int m = 0;
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				e[++m].u = i;
				e[m].v = j;
				cin >> e[m].w;
			}
		}
		int q;
		cin >> q;
		for (int i = 1; i <= q; i++)
		{
			m++;
			cin >> e[m].u >> e[m].v;
			e[m].w = 0;
		}
		sort(e + 1, e + 1 + m);
		for (int i = 1; i <= n; i++)
			p[i] = i;
		int ans = 0;
		for (int i = 1; i <= m; i++)
		{
			int x = find(e[i].u), y = find(e[i].v);
			if (x != y)
			{
				p[x] = y;
				ans += e[i].w;
			}
		}
		cout << ans << endl;
	}
}

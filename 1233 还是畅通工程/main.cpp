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
} e[10001];

int p[101];

int find(int x)
{
	return x == p[x] ? x : p[x] = find(p[x]);
}

int main()
{
	int n;
	cin >> n;
	while (cin >> n)
	{
		if (n == 0) break;
		for (int i = 1; i <= n * (n - 1) / 2; i++)
			cin >> e[i].u >> e[i].v >> e[i].w;
		sort(e + 1, e + 1 + n * (n - 1) / 2);
		for (int i = 1; i <= n; i++)
			p[i] = i;
		int ans = 0;
		for (int i = 1; i <= n * (n - 1) / 2; i++)
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

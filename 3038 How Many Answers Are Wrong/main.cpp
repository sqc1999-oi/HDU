#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
int p[200001], d[200001];

int find(int x)
{
	if (x == p[x]) return x;
	int t = find(p[x]);
	d[x] += d[p[x]];
	return p[x] = t;
}

int main()
{
	ios::sync_with_stdio(false);
	int n, m;
	while (cin >> n >> m)
	{
		memset(d, 0, sizeof d);
		for (int i = 0; i <= n; i++)
			p[i] = i;
		int ans = 0;
		for (int i = 1; i <= m; i++)
		{
			int a, b, s;
			cin >> a >> b >> s;
			a--;
			int x = find(a), y = find(b);
			if (x == y && abs(d[a] - d[b]) != s) ans++;
			if (x != y)
			{
				p[x] = y;
				d[x] = d[b] + s - d[a];
			}
		}
		cout << ans << endl;
	}
}

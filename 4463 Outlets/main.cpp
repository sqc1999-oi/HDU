#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>
using namespace std;

struct edge
{
	int u, v;
	double w;

	bool operator <(const edge &b) const
	{
		return w < b.w;
	}
} e[2501];

int f[51];
pair<double, double> a[51];

int find(int x)
{
	return x == f[x] ? x : f[x] = find(f[x]);
}

int main()
{
	ios::sync_with_stdio(false);
	cout.setf(ios::fixed);
	cout << setprecision(2);
	int n;
	while (cin >> n)
	{
		if (n == 0) break;
		int p, q, m = 0;
		double ans;
		cin >> p >> q;
		if (p > q) swap(p, q);
		for (int i = 1; i <= n; i++)
			cin >> a[i].first >> a[i].second;
		for (int i = 1; i <= n; i++)
		{
			for (int j = i + 1; j <= n; j++)
			{
				double x = sqrt(pow(a[i].first - a[j].first, 2) + pow(a[i].second - a[j].second, 2));
				if (i == p && j == q) ans = x;
				else
				{
					m++;
					e[m].u = i;
					e[m].v = j;
					e[m].w = x;
				}
			}
		}
		sort(e + 1, e + 1 + m);
		for (int i = 1; i <= n; i++)
			f[i] = i;
		f[p] = q;
		for (int i = 1; i <= m; i++)
		{
			int x = find(e[i].u), y = find(e[i].v);
			if (x != y)
			{
				f[x] = y;
				ans += e[i].w;
			}
		}
		cout << ans << endl;
	}
}

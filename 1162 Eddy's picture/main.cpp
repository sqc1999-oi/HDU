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
} e[10001];

int p[101];
pair<double, double> a[101];

int find(int x)
{
	return x == p[x] ? x : p[x] = find(p[x]);
}

int main()
{
	ios::sync_with_stdio(false);
	int n;
	cout.setf(ios::fixed);
	cout << setprecision(2);
	while (cin >> n)
	{
		int m = 0;
		for (int i = 1; i <= n; i++)
			cin >> a[i].first >> a[i].second;
		for (int i = 1; i <= n; i++)
		{
			for (int j = i + 1; j <= n; j++)
			{
				m++;
				e[m].u = i;
				e[m].v = j;
				e[m].w = sqrt((a[i].first - a[j].first) * (a[i].first - a[j].first) + (a[i].second - a[j].second) * (a[i].second - a[j].second));
			}
		}
		sort(e + 1, e + 1 + m);
		for (int i = 1; i <= n; i++)
			p[i] = i;
		double ans = 0;
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

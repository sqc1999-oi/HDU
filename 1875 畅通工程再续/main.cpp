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

pair<int, int> a[101];
int p[101];

int find(int x)
{
	return x == p[x] ? x : p[x] = find(p[x]);
}

int main()
{
	ios::sync_with_stdio(false);
	int t;
	cin >> t;
	cout.setf(ios::fixed);
	cout << setprecision(1);
	while (t--)
	{
		int c;
		cin >> c;
		for (int i = 1; i <= c; i++)
			cin >> a[i].first >> a[i].second;
		int m = 0;
		for (int i = 1; i <= c; i++)
		{
			for (int j = i + 1; j <= c; j++)
			{
				double x = sqrt(pow(a[i].first - a[j].first, 2) + pow(a[i].second - a[j].second, 2));
				if (x >= 10 && x <= 1000)
				{
					x *= 100;
					m++;
					e[m].u = i;
					e[m].v = j;
					e[m].w = x;
				}
			}
		}
		sort(e + 1, e + 1 + m);
		for (int i = 1; i <= c; i++)
			p[i] = i;
		double ans = 0, cnt = 0;
		for (int i = 1; i <= m; i++)
		{
			int x = find(e[i].u), y = find(e[i].v);
			if (x != y)
			{
				p[x] = y;
				ans += e[i].w;
				cnt++;
			}
		}
		if (cnt < c - 1) cout << "oh!";
		else cout << ans;
		cout << endl;
	}
}

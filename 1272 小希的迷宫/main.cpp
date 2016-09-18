#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int p[100001];
bool vis[100001];

int find(int x)
{
	int xx = x;
	while (xx != p[xx])
		xx = p[xx];
	while (x != xx)
	{
		int t = p[x];
		p[x] = xx;
		x = t;
	}
	return x;
}

int main()
{
	ios::sync_with_stdio(false);
	int cnt = 0;
	while (true)
	{
		memset(vis, 0, sizeof vis);
		for (int i = 1; i <= 100000; i++)
			p[i] = i;
		bool flag = true;
		int a, b, xx;
		while (cin >> a >> b)
		{
			if (a <= 0 && b <= 0) break;
			if (!flag) continue;
			int x = find(a), y = find(b);
			if (x == y)
			{
				flag = false;
				continue;
			}
			p[x] = y;
			vis[a] = vis[b] = true;
			xx = a;
		}
		if (flag)
		{
			for (int i = 1; i <= 100000; i++)
			{
				if (vis[i] && find(xx) != find(i))
				{
					flag = false;
					break;
				}
			}
		}
		if (a == -1 && b == -1) break;
		cout << (flag ? "Yes" : "No") << endl;
	}
}

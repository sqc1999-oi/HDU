#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
using namespace std;
int c[50001], n;
inline int lowbit(int x) { return x&-x; }
void Add(int pos, int val)
{
	while (pos <= n)
	{
		c[pos] += val;
		pos += lowbit(pos);
	}
}
int Query(int pos)
{
	int ans = 0;
	while (pos > 0)
	{
		ans += c[pos];
		pos -= lowbit(pos);
	}
	return ans;
}
int main()
{
	ios::sync_with_stdio(false);
	int t;
	cin >> t;
	for (int i = 1; i <= t; i++)
	{
		cout << "Case " << i << ":" << endl;
		memset(c, 0x00, sizeof c);
		cin >> n;
		for (int j = 1; j <= n; j++)
		{
			int x;
			cin >> x;
			Add(j, x);
		}
		string s;
		while (cin >> s&&s != "End")
		{
			int a, b;
			cin >> a >> b;
			if (s == "Add") Add(a, b);
			else if (s == "Sub") Add(a, -b);
			else if (s == "Query") cout << Query(b) - Query(a - 1) << endl;
		}
	}
}

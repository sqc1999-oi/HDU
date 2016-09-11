#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int a[5001], t[5001], n;
inline int lowbit(int x) { return x&-x; }
void Add(int pos,int val)
{
	while (pos <= n)
	{
		t[pos] += val;
		pos += lowbit(pos);
	}
}
int Query(int pos)
{
	int ans = 0;
	while (pos > 0)
	{
		ans += t[pos];
		pos -= lowbit(pos);
	}
	return ans;
}
int main()
{
	ios::sync_with_stdio(false);
	while (cin >> n)
	{
		memset(t, 0x00, sizeof t);
		int ans, cnt = 0;
		for (int i = 1; i <= n; i++)
		{
			cin >> a[i];
			a[i]++;
			cnt += a[i] - 1 - Query(a[i] - 1);
			Add(a[i], 1);
		}
		ans = cnt;
		for (int i = 1; i < n;i++)
		{
			cnt -= a[i] - 1;
			cnt += n - a[i];
			ans = min(ans, cnt);
		}
		cout << ans << endl;
	}
}

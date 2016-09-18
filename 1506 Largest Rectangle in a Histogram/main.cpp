#include <iostream>
#include <algorithm>
using namespace std;
int a[100001], l[100001], r[100001];

int main()
{
	ios::sync_with_stdio(false);
	int n;
	while (cin >> n && n != 0)
	{
		for (int i = 1; i <= n; i++) cin >> a[i];
		l[1] = 1;
		for (int i = 2; i <= n; i++)
		{
			int j = i;
			while (j > 1 && a[i] <= a[j - 1]) j = l[j - 1];
			l[i] = j;
		}
		r[n] = n;
		for (int i = n - 1; i > 0; i--)
		{
			int j = i;
			while (j < n && a[i] <= a[j + 1]) j = r[j + 1];
			r[i] = j;
		}
		long long ans = 0;
		for (int i = 1; i <= n; i++) ans = max(ans, (long long)a[i] * (r[i] - l[i] + 1));
		cout << ans << endl;
	}
}

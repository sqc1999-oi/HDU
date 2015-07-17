#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int flag[201];

int main()
{
	ios::sync_with_stdio(false);
	int t;
	cin >> t;
	while (t--)
	{
		memset(flag, 0x00, sizeof flag);
		int n, ans = 0;
		cin >> n;
		for (int i = 1; i <= n; i++)
		{
			int a, b;
			cin >> a >> b;
			if (a > b) swap(a, b);
			a = (a + 1) / 2;
			b = (b + 1) / 2;
			for (int j = a; j <= b; j++)
			{
				flag[j]++;
				ans = max(ans, flag[j]);
			}
		}
		cout << ans * 10 << endl;
	}
}
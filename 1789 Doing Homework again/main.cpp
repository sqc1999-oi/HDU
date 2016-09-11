#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int d[1001], s[1001], r[1001];
bool flag[1001];

bool cmp(const int& a, const int& b)
{
	return s[a] > s[b];
}

int main()
{
	ios::sync_with_stdio(false);
	int t;
	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;
		for (int i = 1; i <= n; i++) cin >> d[i];
		for (int i = 1; i <= n; i++) cin >> s[i];
		for (int i = 1; i <= n; i++) r[i] = i;
		memset(flag, 0x00, sizeof flag);
		sort(r + 1, r + 1 + n, cmp);
		int ans = 0;
		for (int i = 1; i <= n; i++)
		{
			int j = d[r[i]];
			while (j > 0 && flag[j]) j--;
			if (j == 0) ans += s[r[i]];
			else flag[j] = true;
		}
		cout << ans << endl;
	}
}

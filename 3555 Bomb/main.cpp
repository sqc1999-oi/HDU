#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
long long f[30][10];
string s;

long long dp(int num, int pos, bool ub)
{
	if (pos < 1) return 1;
	if (!ub && f[pos][num] != -1) return f[pos][num];
	long long ans = 0;
	for (int i = 0; i <= (ub ? s[pos - 1] - '0' : 9); i++)
	{
		if (!(num == 4 && i == 9))
		{
			ans += dp(i, pos - 1, ub && s[pos - 1] - '0' == i);
		}
	}
	if (!ub) f[pos][num] = ans;
	return ans;
}

int main()
{
	ios::sync_with_stdio(false);
	memset(f, 0xff, sizeof f);
	int t;
	cin >> t;
	while (t--)
	{
		long long n;
		cin >> n;
		s = "";
		long long x = n;
		do
		{
			s += char(x % 10 + '0');
			x /= 10;
		}
		while (x > 0);
		cout << n + 1 - dp(0, s.length(), true) << endl;
	}
}

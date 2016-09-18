#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
long long f[20][1 << 10][11];
int S[1 << 10][10];
string num;

string to_string(int x)
{
	string ans;
	do
	{
		ans = char(x % 2 + '0') + ans;
		x /= 2;
	}
	while (x != 0);
	while (ans.length() < 10) ans = '0' + ans;
	return ans;
}

inline int count(int s)
{
	int cnt = 0;
	while (s > 0)
	{
		cnt += s & 1;
		s >>= 1;
	}
	return cnt;
}

long long dp(int pos, int s, bool zero, bool ub, int k)
{
	if (pos == 0) return count(s) == k;
	if (!ub && f[pos][s][k] != -1) return f[pos][s][k];
	long long ans = 0;
	for (int i = 0; i <= (ub ? num[pos - 1] - '0' : 9); i++)
	{
		ans += dp(pos - 1, zero && i == 0 ? 0 : S[s][i], zero && i == 0, ub && i == num[pos - 1] - '0', k);
	}
	if (!ub) f[pos][s][k] = ans;
	return ans;
}

int get(int s, int p)
{
	for (int i = p; i <= 9; i++)
		if (1 << i & s)
			return s ^ 1 << i | 1 << p;
	return s | 1 << p;
}

long long solve(long long x, int k)
{
	if (x <= 0) return 0;
	num = "";
	do
	{
		num += x % 10 + '0';
		x /= 10;
	}
	while (x > 0);
	return dp(num.length(), 0, true, true, k);
}

int main()
{
	ios::sync_with_stdio(false);
	for (int i = 0; i < 1 << 10; i++)
		for (int j = 0; j <= 9; j++)
			S[i][j] = get(i, j);
	memset(f, 0xff, sizeof f);
	int t;
	cin >> t;
	for (int i = 1; i <= t; i++)
	{
		long long a, b;
		int k;
		cin >> a >> b >> k;
		cout << "Case #" << i << ": " << solve(b, k) - solve(a - 1, k) << endl;
	}
}

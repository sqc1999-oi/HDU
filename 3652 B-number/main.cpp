#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int f[10][10][13][2];
string s;

int dp(int pos, int num, int mod, bool ub, bool has13)
{
	if (pos == 0) return has13 && mod == 0;
	if (!ub && f[pos][num][mod][has13] != -1) return f[pos][num][mod][has13];
	int ans = 0;
	for (int i = 0; i <= (ub ? s[pos - 1] - '0' : 9); i++)
	{
		ans += dp(pos - 1, i, (mod * 10 + i) % 13, ub && i == s[pos - 1] - '0', has13 || (num == 1 && i == 3));
	}
	if (!ub) f[pos][num][mod][has13] = ans;
	return ans;
}

int main()
{
	ios::sync_with_stdio(false);
	int n;
	memset(f, 0xff, sizeof f);
	while (cin >> n)
	{
		s = "";
		do
		{
			s += char(n % 10 + '0');
			n /= 10;
		}
		while (n > 0);
		cout << dp(s.length(), 0, 0, true, false) << endl;
	}
}

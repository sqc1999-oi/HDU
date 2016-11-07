#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
int dp[10][10];

void init()
{
	memset(dp, 0, sizeof(dp));
	dp[0][0] = 1;
	for (int i = 1; i <= 7; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			for (int k = 0; k < 10; k++)
			{
				if (j != 4 && !(j == 6 && k == 2)) dp[i][j] += dp[i - 1][k];
			}
		}
	}
}

int solve(int n)
{
	init();
	int digit[10];
	int len = 0;
	while (n > 0)
	{
		digit[++len] = n % 10;
		n /= 10;
	}
	digit[len + 1] = 0;
	int ans = 0;
	for (int i = len; i; i--)
	{
		for (int j = 0; j < digit[i]; j++)
		{
			if (j != 4 && !(digit[i + 1] == 6 && j == 2)) ans += dp[i][j];
		}
		if (digit[i] == 4 || (digit[i] == 2 && digit[i + 1] == 6)) break;
	}
	return ans;
}

int main()
{
	int l, r;
	while (cin >> l >> r)
	{
		if (l + r == 0) break;
		else cout << solve(r + 1) - solve(l) << endl;
	}
	return 0;
}

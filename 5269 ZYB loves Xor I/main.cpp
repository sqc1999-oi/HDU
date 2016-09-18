#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int trie[1500001][3], cnt;

void insert(int u, int x, int d)
{
	if (d == 30) return;
	trie[u][2]++;
	int v = x % 2;
	if (trie[u][v] == 0) trie[u][v] = ++cnt;
	insert(trie[u][v], x / 2, d + 1);
}

long long solve(int u, int d)
{
	long long l = 0, r = 0, ans = 0;
	if (trie[u][0] != 0)
	{
		l = trie[trie[u][0]][2];
		(ans += solve(trie[u][0], d * 2)) %= 998244353;
	}
	if (trie[u][1] != 0)
	{
		r = trie[trie[u][1]][2];
		(ans += solve(trie[u][1], d * 2)) %= 998244353;
	}
	ans = (ans + l * r * d) % 998244353;
	return ans;
}

int main()
{
	ios::sync_with_stdio(false);
	int t;
	cin >> t;
	for (int k = 1; k <= t; k++)
	{
		memset(trie, 0x00, sizeof trie);
		cnt = 0;
		int n;
		cin >> n;
		for (int i = 1; i <= n; i++)
		{
			int a;
			cin >> a;
			insert(0, a, 0);
		}
		cout << "Case #" << k << ": " << solve(0, 1) * 2 % 998244353 << endl;
	}
}

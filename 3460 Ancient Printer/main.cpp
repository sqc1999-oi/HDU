#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
using namespace std;
int trie[500001][26], cnt;

void insert(int u, const string& s, int pos)
{
	if (pos == s.length()) return;
	int v = s[pos] - 'a';
	if (trie[u][v] == 0) trie[u][v] = ++cnt;
	insert(trie[u][v], s, pos + 1);
}

int main()
{
	ios::sync_with_stdio(false);
	int n;
	while (cin >> n)
	{
		memset(trie, 0x00, sizeof trie);
		cnt = 0;
		int m = 0;
		for (int i = 1; i <= n; i++)
		{
			string s;
			cin >> s;
			insert(0, s, 0);
			m = max(m, (int)s.length());
		}
		cout << cnt * 2 + n - m << endl;
	}
}

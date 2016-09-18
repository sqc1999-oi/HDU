#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
int Next[200001];

int main()
{
	ios::sync_with_stdio(false);
	int t;
	cin >> t;
	while (t--)
	{
		int n;
		string s;
		cin >> n >> s;
		int j = 0;
		Next[0] = Next[1] = 0;
		for (int i = 1; i < n; i++)
		{
			while (j > 0 && s[i] != s[j])
				j = Next[j];
			if (s[i] == s[j]) j++;
			Next[i + 1] = j;
		}
		int ans = n % 10007;
		for (int i = 1; i <= n; i++)
			if (Next[i] > 0) (++ans) %= 10007;
		cout << ans << endl;
	}
}

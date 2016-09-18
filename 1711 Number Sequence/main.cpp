#include <iostream>
#include <algorithm>
using namespace std;
int a[1000000], b[10000], Next[10001];

int main()
{
	ios::sync_with_stdio(false);
	int t;
	cin >> t;
XX: while (t--)
	{
		int n, m;
		cin >> n >> m;
		for (int i = 0; i < n; i++)
			cin >> a[i];
		for (int i = 0; i < m; i++)
			cin >> b[i];
		int j = 0;
		Next[0] = Next[1] = 0;
		for (int i = 1; i < m; i++)
		{
			while (j > 0 && b[i] != b[j])
				j = Next[j];
			if (b[i] == b[j]) j++;
			Next[i + 1] = j;
		}
		j = 0;
		for (int i = 0; i < n; i++)
		{
			while (j > 0 && a[i] != b[j])
				j = Next[j];
			if (a[i] == b[j]) j++;
			if (j == m)
			{
				cout << i - m + 2 << endl;
				goto XX;
			}
		}
		cout << -1 << endl;
	}
}

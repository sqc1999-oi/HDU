#include <iostream>
#include <algorithm>
using namespace std;
double f[10001];

int main()
{
	ios::sync_with_stdio(false);
	int t;
	cin >> t;
	while (t--)
	{
		double P;
		int n;
		cin >> P >> n;
		fill(f, f + 10001, 0);
		f[0] = 1;
		for (int i = 1; i <= n; i++)
		{
			int m;
			double p;
			cin >> m >> p;
			for (int j = n * 100; j >= m; j--)
				f[j] = max(f[j], f[j - m] * (1 - p));
		}
		for (int i = n * 100; i >= 0; i--)
		{
			if (f[i] >= 1 - P)
			{
				cout << i << endl;
				break;
			}
		}
	}
}

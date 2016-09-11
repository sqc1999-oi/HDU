#include <iostream>
#include <algorithm>
using namespace std;
int a[10001], f[10001], l[10001];

int main()
{
	ios::sync_with_stdio(false);
	int k;
	while (cin >> k && k != 0)
	{
		for (int i = 1; i <= k; i++) cin >> a[i];
		int Ans = -1, L = a[1], R = a[k], l = a[1], sum = 0;
		for (int r = 1; r <= k; r++)
		{
			if (sum < 0) l = sum = a[r];
			else sum += a[r];
			if (sum > Ans)
			{
				Ans = sum;
				L = l;
				R = a[r];
			}
		}
		if (Ans < 0) Ans = 0;
		cout << Ans << ' ' << L << ' ' << R << endl;
	}
}

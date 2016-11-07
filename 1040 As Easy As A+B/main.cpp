#include <iostream>
#include <algorithm>
using namespace std;
int a[1001];

int main()
{
	ios::sync_with_stdio(false);
	int t;
	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;
		for (int i = 1; i <= n; i++)
			cin >> a[i];
		sort(a + 1, a + 1 + n);
		for (int i = 1; i < n; i++)
			cout << a[i] << ' ';
		cout << a[n] << endl;
	}
}

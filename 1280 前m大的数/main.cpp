#include <iostream>
#include <algorithm>
#include <queue>
#include <functional>
using namespace std;
int a[3001];

bool cmp(int a, int b)
{
	return a > b;
}

int main()
{
	ios::sync_with_stdio(false);
	int n, m;
	while (cin >> n >> m)
	{
		priority_queue<int, vector<int>, greater<int>> q;
		for (int i = 1; i <= n; i++)
			cin >> a[i];
		for (int i = 1; i <= n; i++)
		{
			for (int j = i + 1; j <= n; j++)
			{
				q.push(a[i] + a[j]);
				if (q.size() > m) q.pop();
			}
		}
		for (int i = 1; i <= m; i++)
			a[i] = q.top() , q.pop();
		for (int i = m; i > 1; i--)
			cout << a[i] << ' ';
		cout << a[1] << endl;
	}
}

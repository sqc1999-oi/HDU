#include <iostream>
#include <algorithm>
using namespace std;

int exgcd(int a, int b, int &x, int &y)
{
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}
	int tmp = exgcd(b, a % b, y, x);
	y -= x * (a / b);
	return tmp;
}

int main()
{
	ios::sync_with_stdio(false);
	int t;
	cin >> t;
	while (t--)
	{
		int n, b;
		cin >> n >> b;
		int x, y;
		exgcd(b, 9973, x, y);
		x = (x % 9973 + 9973) % 9973;
		cout << n * x % 9973 << endl;
	}
}
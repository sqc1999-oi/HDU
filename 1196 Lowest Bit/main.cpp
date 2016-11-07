#include <iostream>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	int n;
	while (cin >> n && n != 0)
	{
		cout << (n & -n) << endl;
	}
}

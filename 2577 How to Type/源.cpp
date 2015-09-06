#include <iostream>
#include <algorithm>
#include <string>
#include <cctype>
using namespace std;
int f[101][2];
int main()
{
	ios::sync_with_stdio(false);
	int t;
	cin >> t;
	while (t--)
	{
		string s;
		cin >> s;
		s = ' ' + s;
		f[0][0] = 0;
		f[0][1] = 1;
		for (int i = 1; i < s.length(); i++)
		{
			if (islower(s[i]))
			{
				f[i][0] = min(f[i - 1][0] + 1, f[i - 1][1] + 2);
				f[i][1] = min(f[i - 1][0] + 2, f[i - 1][1] + 2);
			}
			else
			{
				f[i][0] = min(f[i - 1][0] + 2, f[i - 1][1] + 2);
				f[i][1] = min(f[i - 1][0] + 2, f[i - 1][1] + 1);
			}
		}
		cout << min(f[s.length() - 1][0], f[s.length() - 1][1] + 1) << endl;
	}
}
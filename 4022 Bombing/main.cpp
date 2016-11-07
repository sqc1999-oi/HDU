#include <iostream>
#include <algorithm>
#include <map>
#include <set>
using namespace std;
map<int, multiset<int> > r, c;
int bomb(map<int, multiset<int> >& a, map<int, multiset<int> > &b, int x)
{
	int ret = a[x].size();
	for (multiset<int>::iterator i = a[x].begin(); i != a[x].end(); ++i)
	{
		b[*i].erase(x);
	}
	a[x].clear();
	return ret;
}
int main()
{
	ios::sync_with_stdio(false);
	int n, m;
	while (cin >> n >> m && !(n == 0 && m == 0))
	{
		r.clear();
		c.clear();
		for (int i = 1; i <= n; i++)
		{
			int x, y;
			cin >> x >> y;
			r[x].insert(y);
			c[y].insert(x);
		}
		for (int i = 1; i <= m; i++)
		{
			int x, y;
			cin >> x >> y;
			cout << (x ? bomb(c, r, y) : bomb(r, c, y)) << endl;
		}
		cout << endl;
	}
}

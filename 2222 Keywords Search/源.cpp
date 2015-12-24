#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <queue>
using namespace std;
struct node
{
	node *link[26], *f, *last;
	int val;
} cache[500001];
int pos;
node *get_node()
{
	return &cache[pos++];
}
int main()
{
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	while (T--)
	{
		pos = 0;
		memset(cache, 0x00, sizeof cache);
		int n;
		cin >> n;
		node *r = get_node();
		r->f = r->last = r;
		for (int i = 0; i < n; i++)
		{
			string s;
			cin >> s;
			node *cu = r;
			for (int j = 0; j < s.length(); j++)
			{
				if (!cu->link[s[j] - 'a'])
					cu->link[s[j] - 'a'] = get_node();
				cu = cu->link[s[j] - 'a'];
			}
			cu->val++;
		}
		queue<node*> q;
		for (int i = 0; i < 26; i++)
		{
			node *&u = r->link[i];
			if (u)
			{
				q.push(u);
				u->last = u->f = r;
			}
			else u = r;
		}
		while (!q.empty())
		{
			node *u = q.front();
			q.pop();
			for (int i = 0; i < 26; i++)
			{
				node *&v = u->link[i];
				if (v)
				{
					q.push(v);
					node *cu = u->f;
					while (cu != r && !cu->link[i]) cu = cu->f;
					v->f = cu->link[i];
					v->last = v->f->val ? v->f : v->f->last;
				}
				else v = u->f->link[i];
			}
		}
		string s;
		cin >> s;
		int ans = 0;
		node *j = r;
		for (int i = 0; i < s.length(); i++)
		{
			j = j->link[s[i] - 'a'];
			node *x = j->val ? j : j->last;
			while (x != r)
			{
				ans += x->val;
				x->val = 0;
				x = x->last;
			}
		}
		cout << ans << endl;
	}
}
#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
using namespace std;
const int N = 1e5;
struct splay_node
{
	static splay_node *nul;
	struct constructor
	{
		constructor()
		{
			nul = new splay_node;
			nul->l = nul->r = nul->p = nul;
		}
	};
	static constructor ctor;
	splay_node *l, *r, *p;
	int v;
	splay_node *m;
	bool rev_f;
	splay_node() :l(nul), r(nul), p(nul), v(INT_MAX), m(this), rev_f() {}
	bool is_root() { return p == nul || p->l != this&&p->r != this; }
	void maintain()
	{
		m = l->m;
		if (r->m->v < m->v) m = r->m;
		if (v < m->v) m = this;
	}
	void reverse()
	{
		if (this == nul) return;
		swap(l, r);
		rev_f ^= 1;
	}
	void push_down()
	{
		if (!rev_f) return;
		l->reverse();
		r->reverse();
		rev_f = false;
	}
	void transplant(splay_node *x)
	{
		x->p = p;
		if (p->l == this) p->l = x;
		else if (p->r == this) p->r = x;
	}
	void left_rotate()
	{
		splay_node *x = r;
		r = x->l;
		r->p = this;
		transplant(x);
		x->l = this;
		p = x;
		maintain();
		x->maintain();
	}
	void right_rotate()
	{
		splay_node *x = l;
		l = x->r;
		l->p = this;
		transplant(x);
		x->r = this;
		p = x;
		maintain();
		x->maintain();
	}
	void splay()
	{
		static splay_node *st[N];
		int k = 0;
		splay_node *t = this;
		while (!t->is_root())
		{
			st[k++] = t;
			t = t->p;
		}
		st[k++] = t;
		while (k > 0) st[--k]->push_down();
		while (!is_root())
		{
			if (p->is_root())
				if (p->l == this) p->right_rotate();
				else p->left_rotate();
			else
			{
				splay_node *x = p->p;
				if (p->l == this)
					if (x->l == p) x->right_rotate(), p->right_rotate();
					else p->right_rotate(), x->left_rotate();
				else
					if (x->r == p) x->left_rotate(), p->left_rotate();
					else p->left_rotate(), x->right_rotate();
			}
		}
	}
};
splay_node *splay_node::nul;
splay_node::constructor splay_node::ctor;
void access(splay_node *n)
{
	splay_node *x = n, *y = splay_node::nul;
	while (x != splay_node::nul)
	{
		x->splay();
		x->r = y;
		x->maintain();
		y = x;
		x = x->p;
	}
	n->splay();
}
void change_root(splay_node *x)
{
	access(x);
	x->reverse();
}
void link(splay_node *x, splay_node *y)
{
	change_root(y);
	y->p = x;
	access(y);
}
void extract(splay_node *x, splay_node *y)
{
	change_root(x);
	access(y);
}
void cut(splay_node *x, splay_node *y)
{
	extract(x, y);
	y->l = x->p = splay_node::nul;
	y->maintain();
}
splay_node *find_root(splay_node *x)
{
	while (x->p != splay_node::nul) x = x->p;
	return x;
}
splay_node a[N * 2 - 1];
int ans[N + 1];
struct { int x, y; } e[N - 1];
int solve(int x, int y, int w)
{
	static int cnt = N;
	int ret = 0;
	if (x == y) return ret;
	if (find_root(a + x) != find_root(a + y))
	{
		ret = w;
		(a + cnt)->v = w;
		(a + cnt)->m = a + cnt;
		link(a + x, a + cnt);
		link(a + y, a + cnt);
		e[cnt - N].x = x;
		e[cnt - N].y = y;
		cnt++;
	}
	else
	{
		extract(a + x, a + y);
		splay_node *t = (a + y)->m;
		if (t->v < w)
		{
			ret = w - t->v;
			cut(a + e[t - a - N].x, t);
			cut(a + e[t - a - N].y, t);
			*t = splay_node();
			t->v = w;
			t->m = t;
			link(a + x, t);
			link(a + y, t);
			e[t - a - N].x = x;
			e[t - a - N].y = y;
		}
	}
	return ret;
}
int main()
{
	ios::sync_with_stdio(false);
	for (int i = 1; i <= N; i++)
	{
		ans[i] = ans[i - 1];
		for (int j = 1; j*j <= i; j++)
			if (i%j == 0)
			{
				ans[i] += solve(i - 1, j - 1, j);
				if (j*j != i) ans[i] += solve(i - 1, i / j - 1, i / j);
			}
	}
	int n;
	while (cin >> n) cout << ans[n] << endl;
}

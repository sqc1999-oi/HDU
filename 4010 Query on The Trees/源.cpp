#include <iostream>
#include <algorithm>
using namespace std;
const int N = 3e5;
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
	int v, m;
	bool rev_f;
	int add_f;
	splay_node() :l(nul), r(nul), p(nul), v(), m(), rev_f(), add_f() {}
	bool is_root() { return p == nul || p->l != this&&p->r != this; }
	void maintain() { m = max(v, max(l->m, r->m)); }
	void reverse()
	{
		if (this == nul) return;
		swap(l, r);
		rev_f ^= 1;
	}
	void add(int val)
	{
		if (this == nul) return;
		add_f += val;
		v += val;
		m += val;
	}
	void push_down()
	{
		if (rev_f)
		{
			l->reverse();
			r->reverse();
			rev_f = false;
		}
		if (add_f > 0)
		{
			l->add(add_f);
			r->add(add_f);
			add_f = 0;
		}
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
void extract(splay_node *x,splay_node *y)
{
	change_root(x);
	access(y);
}
void cut(splay_node *x, splay_node *y)
{
	extract(x, y);
	y->l = y->l->p = splay_node::nul;
	y->maintain();
}
splay_node *find_root(splay_node *x)
{
	while (x->p != splay_node::nul) x = x->p;
	return x;
}
splay_node *splay_node::nul;
splay_node::constructor splay_node::ctor;
splay_node a[N];
int main()
{
	ios::sync_with_stdio(false);
	int n;
	while (cin >> n)
	{
		for (int i = 0; i < n; i++) a[i] = splay_node();
		for (int i = 0; i < n - 1; i++)
		{
			int x, y;
			cin >> x >> y;
			link(a + x - 1, a + y - 1);
		}
		for (int i = 0; i < n; i++)
		{
			int w;
			cin >> w;
			access(a + i);
			(a + i)->v = w;
			(a + i)->maintain();
		}
		int q;
		cin >> q;
		while (q--)
		{
			int op;
			cin >> op;
			if (op == 1)
			{
				int x, y;
				cin >> x >> y;
				if (find_root(a + x - 1) == find_root(a + y - 1)) cout << -1 << endl;
				else link(a + x - 1, a + y - 1);
			}
			else if (op == 2)
			{
				int x, y;
				cin >> x >> y;
				if (x == y || find_root(a + x - 1) != find_root(a + y - 1)) cout << -1 << endl;
				else cut(a + x - 1, a + y - 1);
			}
			else if (op == 3)
			{
				int w, x, y;
				cin >> w >> x >> y;
				if (find_root(a + x - 1) != find_root(a + y - 1)) cout << -1 << endl;
				else
				{
					extract(a + x - 1, a + y - 1);
					(a + y - 1)->add(w);
				}
			}
			else if (op == 4)
			{
				int x, y;
				cin >> x >> y;
				if (find_root(a + x - 1) != find_root(a + y - 1)) cout << -1 << endl;
				else
				{
					extract(a + x - 1, a + y - 1);
					cout << (a + y - 1)->m << endl;
				}
			}
		}
		cout << endl;
	}
}

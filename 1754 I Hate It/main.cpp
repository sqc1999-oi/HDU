#include <iostream>
#include <algorithm>
using namespace std;

struct Node
{
	int L, R, Val;
	Node *l, *r;
};

struct SegmentTree
{
private:
	Node* root;

	Node* build(int l, int r)
	{
		if (l == r) return new Node { l,r,0,NULL,NULL };
		return new Node { l,r,0,build(l, (l + r) / 2),build((l + r) / 2 + 1, r) };
	}

	void update(int pos, int val, Node* n)
	{
		if (n->L == n->R) n->Val = val;
		else
		{
			if (pos <= n->l->R) update(pos, val, n->l);
			else update(pos, val, n->r);
			n->Val = max(n->l->Val, n->r->Val);
		}
	}

	int query(int l, int r, Node* n)
	{
		if (n->L == l && n->R == r) return n->Val;
		if (r <= n->l->R) return query(l, r, n->l);
		if (l >= n->r->L) return query(l, r, n->r);
		return max(query(l, n->l->R, n->l), query(n->r->L, r, n->r));
	}

public:
	SegmentTree(int n)
	{
		root = build(1, n);
	}

	void Update(int pos, int val)
	{
		update(pos, val, root);
	}

	int Query(int l, int r)
	{
		return query(l, r, root);
	}
};

SegmentTree T(200000);

int main()
{
	ios::sync_with_stdio(false);
	int n, m;
	while (cin >> n >> m)
	{
		for (int i = 1; i <= n; i++)
		{
			int x;
			cin >> x;
			T.Update(i, x);
		}
		for (int i = 1; i <= m; i++)
		{
			char ch;
			int a, b;
			cin >> ch >> a >> b;
			if (ch == 'Q') cout << T.Query(a, b) << endl;
			else if (ch == 'U') T.Update(a, b);
		}
	}
}

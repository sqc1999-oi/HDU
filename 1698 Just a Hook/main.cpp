#include <iostream>
#include <algorithm>
using namespace std;

struct Node
{
	int L, R, Sum, Mark;
	bool HasMark;
	Node *LC, *RC;
};

struct SegmentTree
{
private:
	Node* root;

	Node* build(int l, int r)
	{
		if (l == r) return new Node { l,r,0,0,false,NULL,NULL };
		return new Node { l,r,0,0,false,build(l, (l + r) / 2),build((l + r) / 2 + 1, r) };
	}

	void push_down(Node* n)
	{
		if (!n->HasMark) return;
		n->LC->Mark = n->RC->Mark = n->Mark;
		n->LC->Sum = n->Mark * (n->LC->R - n->LC->L + 1);
		n->RC->Sum = n->Mark * (n->RC->R - n->RC->L + 1);
		n->LC->HasMark = n->RC->HasMark = true;
		n->HasMark = false;
	}

	void update(int l, int r, int val, Node* n)
	{
		if (n->L == l && n->R == r)
		{
			n->HasMark = true;
			n->Mark = val;
			n->Sum = val * (r - l + 1);
		}
		else
		{
			push_down(n);
			if (r <= n->LC->R) update(l, r, val, n->LC);
			else if (l >= n->RC->L) update(l, r, val, n->RC);
			else
			{
				update(l, n->LC->R, val, n->LC);
				update(n->RC->L, r, val, n->RC);
			}
			n->Sum = n->LC->Sum + n->RC->Sum;
		}
	}

	int query(int l, int r, Node* n)
	{
		if (n->L == l && n->R == r) return n->Sum;
		push_down(n);
		if (r <= n->LC->R) return query(l, r, n->LC);
		if (l >= n->RC->L) return query(l, r, n->RC);
		return query(l, n->LC->R, n->LC) + query(n->RC->L, r, n->RC);
	}

public:
	SegmentTree(int n)
	{
		root = build(1, n);
	}

	void Update(int l, int r, int val)
	{
		update(l, r, val, root);
	}

	int Query(int l, int r)
	{
		return query(l, r, root);
	}
} T(100000);

int main()
{
	ios::sync_with_stdio(false);
	int t;
	cin >> t;
	for (int i = 1; i <= t; i++)
	{
		int n, q;
		cin >> n >> q;
		T.Update(1, n, 1);
		for (int j = 1; j <= q; j++)
		{
			int a, b, c;
			cin >> a >> b >> c;
			T.Update(a, b, c);
		}
		cout << "Case " << i << ": The total value of the hook is " << T.Query(1, n) << "." << endl;
	}
}

#include <iostream>
#include <algorithm>
using namespace std;

struct Node
{
	int L, R, Val;
	Node *LC, *RC;
};

struct SegmentTree
{
private:
	Node* root;

	Node* build(int l, int r, int val)
	{
		if (l == r) return new Node{ l,r,val,NULL,NULL };
		return new Node{ l,r,val,build(l, (l + r) / 2, val),build((l + r) / 2 + 1, r, val) };
	}

	void destroy(Node* n)
	{
		if (n == NULL) return;
		destroy(n->LC);
		destroy(n->RC);
		delete n;
	}

	int update(int val, Node* n)
	{
		if (n->L == n->R)
		{
			n->Val -= val;
			return n->L;
		}
		int pos = -1;
		if (val <= n->LC->Val) pos = update(val, n->LC);
		else if (val <= n->RC->Val) pos = update(val, n->RC);
		n->Val = max(n->LC->Val, n->RC->Val);
		return pos;
	}

public:
	SegmentTree(int n, int val)
	{
		root = build(1, n, val);
	}

	~SegmentTree()
	{
		destroy(root);
	}

	int Update(int val)
	{
		return update(val, root);
	}
};

int main()
{
	ios::sync_with_stdio(false);
	int h, w, n;
	while (cin >> h >> w >> n)
	{
		SegmentTree* T = new SegmentTree(min(h, n + 1), w);
		for (int i = 1; i <= n; i++)
		{
			int x;
			cin >> x;
			cout << T->Update(x) << endl;
		}
		delete T;
	}
}

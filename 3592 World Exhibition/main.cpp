#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

struct Edge
{
	int To, Pow, Next;

	Edge(int to, int pow, int next) :
		To(to), Pow(pow), Next(next) { }

	Edge() { }
} E[30000];

int G[1001], dis[1001], cnt, Cnt[1001];
bool inq[1001];

void AddEdge(int from, int to, int pow)
{
	E[++cnt] = Edge(to, pow, G[from]);
	G[from] = cnt;
}

int main()
{
	ios::sync_with_stdio(false);
	int t;
	cin >> t;
XX: while (t--)
	{
		memset(G, 0, sizeof G);
		cnt = 0;
		int n, x, y;
		cin >> n >> x >> y;
		for (int i = 2; i <= n; i++)
			AddEdge(i, i - 1, 0);
		for (int i = 1; i <= x; i++)
		{
			int a, b, c;
			cin >> a >> b >> c;
			if (a > b) swap(a, b);
			AddEdge(a, b, c);
		}
		for (int i = 1; i <= y; i++)
		{
			int a, b, c;
			cin >> a >> b >> c;
			if (a > b) swap(a, b);
			AddEdge(b, a, -c);
		}
		memset(dis, 0x3f, sizeof dis);
		memset(Cnt, 0, sizeof Cnt);
		memset(inq, 0, sizeof inq);
		dis[1] = 0;
		queue<int> q;
		q.push(1);
		inq[1] = true;
		while (!q.empty())
		{
			int u = q.front();
			q.pop();
			inq[u] = false;
			for (int i = G[u]; i != 0; i = E[i].Next)
			{
				int &v = E[i].To;
				int tmp = dis[v];
				dis[v] = min(dis[v], dis[u] + E[i].Pow);
				if (tmp != dis[v] && !inq[v])
				{
					if (++Cnt[v] > n)
					{
						cout << -1 << endl;
						goto XX;
					}
					q.push(v);
					inq[v] = true;
				}
			}
		}
		if (dis[n] == 0x3f3f3f3f) cout << -2;
		else cout << dis[n];
		cout << endl;
	}
}

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
} E[10000];

int G[1001], dis[1001], cnt, Cnt[1001], r[1001], a[1001];
bool inq[1001];

void AddEdge(int from, int to, int pow)
{
	E[++cnt] = Edge(to, pow, G[from]);
	G[from] = cnt;
}

bool cmp(int x, int y)
{
	return a[x] < a[y];
}

int main()
{
	ios::sync_with_stdio(false);
	int t;
	cin >> t;
	for (int i = 1; i <= t; i++)
	{
		cout << "Case " << i << ": ";
		memset(G, 0, sizeof G);
		cnt = 0;
		int n, d;
		cin >> n >> d;
		for (int i = 1; i <= n; i++)
		{
			cin >> a[i];
			r[i] = i;
			if (i > 1) AddEdge(i, i - 1, -1);
		}
		sort(r + 1, r + 1 + n, cmp);
		for (int i = 2; i <= n; i++)
			AddEdge(min(r[i], r[i - 1]), max(r[i], r[i - 1]), d);
		int s = min(r[1], r[n]), t = max(r[1], r[n]);
		memset(dis, 0x7f, sizeof dis);
		memset(Cnt, 0, sizeof Cnt);
		memset(inq, 0, sizeof inq);
		dis[s] = 0;
		queue<int> q;
		q.push(s);
		inq[s] = true;
		bool flag = true;
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
						flag = false;
						break;
					}
					q.push(v);
					inq[v] = true;
				}
			}
			if (!flag) break;
		}
		cout << (flag ? dis[t] : -1) << endl;
	}
}

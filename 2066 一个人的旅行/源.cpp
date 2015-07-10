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
} E[10000001];

int G[1001], dis[1001], cnt;
bool inq[1001];

void AddEdge(int from, int to, int pow)
{
	E[++cnt] = Edge(to, pow, G[from]);
	G[from] = cnt;
	E[++cnt] = Edge(from, pow, G[to]);
	G[to] = cnt;
}

int main()
{
	ios::sync_with_stdio(false);
	int t, s, d;
	while (cin >> t >> s >> d)
	{
		cnt = 0;
		memset(G, 0, sizeof G);
		for (int i = 1; i <= t; i++)
		{
			int a, b, time;
			cin >> a >> b >> time;
			AddEdge(a, b, time);
		}
		for (int i = 1; i <= s; i++)
		{
			int x;
			cin >> x;
			AddEdge(0, x, 0);
		}
		memset(dis, 0x3f, sizeof dis);
		dis[0] = 0;
		queue<int> q;
		q.push(0);
		inq[0] = true;
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
					q.push(v);
					inq[v] = true;
				}
			}
		}
		int ans = 0x7fffffff;
		for (int i = 1; i <= d; i++)
		{
			int x;
			cin >> x;
			ans = min(ans, dis[x]);
		}
		cout << ans << endl;
	}
}

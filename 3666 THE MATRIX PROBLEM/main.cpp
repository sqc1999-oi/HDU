#include <iostream>
#include <algorithm>
#include <stack>
#include <cstring>
#include <cmath>
using namespace std;

struct Edge
{
	int To, Next;
	double Pow;

	Edge(int to, double pow, int next) :
		To(to), Pow(pow), Next(next) { }

	Edge() { }
} E[1000001];

int G[1001], cnt, Cnt[1001];
double dis[1001];
bool inq[1001];

void AddEdge(int from, int to, double pow)
{
	E[++cnt] = Edge(to, pow, G[from]);
	G[from] = cnt;
}

int a[401][401];

int main()
{
	ios::sync_with_stdio(false);
	int n, m, l, u;
	while (cin >> n >> m >> l >> u)
	{
		memset(G, 0, sizeof G);
		cnt = 0;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
			{
				int w;
				cin >> w;
				AddEdge(j + n, i, log(u) - log(w));
				AddEdge(i, j + n, log(w) - log(l));
			}
		for (int i = 1; i <= n + m; i++)
			AddEdge(0, i, 0);
		memset(dis, 0x3f, sizeof dis);
		memset(Cnt, 0, sizeof Cnt);
		memset(inq, 0, sizeof inq);
		dis[0] = 0;
		stack<int> q;
		q.push(0);
		inq[0] = true;
		bool flag = true;
		while (!q.empty())
		{
			int u = q.top();
			q.pop();
			inq[u] = false;
			for (int i = G[u]; i != 0; i = E[i].Next)
			{
				int &v = E[i].To;
				double tmp = dis[v];
				dis[v] = min(dis[v], dis[u] + E[i].Pow);
				if (tmp != dis[v] && !inq[v])
				{
					if (++Cnt[v] > n + m + 1)
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
		cout << (flag ? "YES" : "NO") << endl;
	}
}

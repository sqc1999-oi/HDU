#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
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
} E[1000001];

int G[1001], dis[1001], cnt, Cnt[1001];
bool inq[1001];

void AddEdge(int from, int to, int pow)
{
	E[++cnt] = Edge(to, pow, G[from]);
	G[from] = cnt;
}

int t[1001];

int main()
{
	int n, m = 0;
XX: while (~scanf("%d", &n))
	{
		memset(G, 0, sizeof G);
		cnt = 0;
		if (n == 0) break;
		printf("Case %d:\n", ++m);
		for (int i = 1; i <= n; i++)
			scanf("%d", &t[i]);
		while (true)
		{
			char s[4];
			scanf("%s", s);
			if (strcmp(s, "#") == 0) break;
			int a, b;
			scanf("%d%d", &a, &b);
			if (strcmp(s, "FAS") == 0) AddEdge(b, a, -t[a]);
			else if (strcmp(s, "FAF") == 0) AddEdge(b, a, t[b] - t[a]);
			else if (strcmp(s, "SAF") == 0) AddEdge(b, a, t[b]);
			else if (strcmp(s, "SAS") == 0) AddEdge(b, a, 0);
		}
		for (int i = 1; i <= n; i++)
			AddEdge(0, i, 0);
		memset(dis, 0x80, sizeof dis);
		memset(Cnt, 0, sizeof Cnt);
		memset(inq, 0, sizeof inq);
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
				dis[v] = max(dis[v], dis[u] + E[i].Pow);
				if (tmp != dis[v] && !inq[v])
				{
					if (++Cnt[v] > n)
					{
						printf("impossible\n\n");
						goto XX;
					}
					q.push(v);
					inq[v] = true;
				}
			}
		}
		for (int i = 1; i <= n; i++)
			printf("%d %d\n", i, dis[i]);
		puts("");
	}
}

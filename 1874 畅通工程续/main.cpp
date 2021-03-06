﻿#include <iostream>
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
} E[1001];

int G[200], dis[200], cnt;
bool inq[101];

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
	int n, m;
	while (cin >> n >> m)
	{
		cnt = 0;
		memset(G, 0, sizeof G);
		for (int i = 1; i <= m; i++)
		{
			int a, b, c;
			cin >> a >> b >> c;
			AddEdge(a, b, c);
		}
		int s, t;
		cin >> s >> t;
		memset(dis, 0x3f, sizeof dis);
		dis[s] = 0;
		queue<int> q;
		q.push(s);
		inq[s] = true;
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
		if (dis[t] == 0x3f3f3f3f) cout << -1 << endl;
		else cout << dis[t] << endl;
	}
}

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>
#include <cstring>
#pragma comment(linker, "/STACK:1024000000,1024000000")
using namespace std;
int p[100001];
bool vis[100001];

struct Edge
{
	int To, Pow, Next;

	Edge(int to, int pow, int next) :
		To(to), Pow(pow), Next(next) { }

	Edge() { }
} E[2000001];

int G[100001];

int find(int x)
{
	return x == p[x] ? x : p[x] = find(p[x]);
}

int ans, pos;

void dfs(int u, int fa, int d)
{
	vis[u] = true;
	if (d > ans)
	{
		ans = d;
		pos = u;
	}
	for (int i = G[u]; i != 0; i = E[i].Next)
		if (E[i].To != fa) dfs(E[i].To, u, d + E[i].Pow);
}

int main()
{
	int n, m;
	while (~scanf("%d%d", &n, &m))
	{
		memset(vis, 0, sizeof vis);
		memset(G, 0, sizeof G);
		for (int i = 1; i <= n; i++)
			p[i] = i;
		bool flag = false;
		for (int i = 1; i <= m; i++)
		{
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			if (flag) continue;
			int x = find(a), y = find(b);
			if (x == y)
			{
				flag = true;
				continue;
			}
			else p[x] = y;
			E[i * 2 - 1] = Edge(b, c, G[a]);
			G[a] = i * 2 - 1;
			E[i * 2] = Edge(a, c, G[b]);
			G[b] = i * 2;
		}
		if (!flag)
		{
			int res = 0;
			for (int i = 1; i <= n; i++)
			{
				if (!vis[i])
				{
					ans = 0;
					dfs(1, 0, 0);
					ans = 0;
					dfs(pos, 0, 0);
					res = max(res, ans);
				}
			}
			printf("%d\n", res);
		}
		else puts("YES");
	}
}

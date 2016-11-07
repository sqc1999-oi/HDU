#pragma warning(disable:4018)
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdarg>
#include <cctype>
#include <cstring>
using namespace std;
const int N = 30000, M = 14;
typedef pair<int, long long> pil;

struct gr
{
	long long dis[2];
	int cnt[2];
} p[N][M], c[N * 2][M];

vector<pil> f[N];
vector<int> g[N], e;
bool flag[N];
int sz[N], len[N * 2], a[N], A[N], ch[N];
long long dep[N];

void get_nodes(int u, int fa, vector<int> &vi)
{
	vi.push_back(u);
	for (int i = 0; i < g[u].size(); i++)
	{
		int v = e[g[u][i]];
		if (v != fa && !flag[v])
			get_nodes(v, u, vi);
	}
}

void calc_size(int u, int fa)
{
	sz[u] = 1;
	for (int i = 0; i < g[u].size(); i++)
	{
		int v = e[g[u][i]];
		if (v != fa && !flag[v])
		{
			calc_size(v, u);
			sz[u] += sz[v];
		}
	}
}

void calc_dep(int u, int fa)
{
	for (int i = 0; i < g[u].size(); i++)
	{
		int v = e[g[u][i]];
		if (v != fa && !flag[v])
		{
			dep[v] = dep[u] + len[g[u][i]];
			calc_dep(v, u);
		}
	}
}

void get_focus(int u, int fa, int n, int &ans, int &min)
{
	int max = n - sz[u];
	for (int i = 0; i < g[u].size(); i++)
	{
		int v = e[g[u][i]];
		if (v != fa && !flag[v])
		{
			max = ::max(max, sz[v]);
			get_focus(v, u, n, ans, min);
		}
	}
	if (max < min)
	{
		min = max;
		ans = u;
	}
}

void calc_ans(int u, gr *d, bool flag)
{
	vector<int> vi;
	get_nodes(u, -1, vi);
	for (int i = 0; i < vi.size(); i++)
	{
		if (flag) f[vi[i]].push_back(pil(u, dep[vi[i]]));
		for (int j = 0; j < M; j++)
		{
			d[j].dis[0] += dep[vi[i]];
			d[j].cnt[0]++;
		}
	}
}

void solve(int u, int fa)
{
	calc_size(u, -1);
	int x = INT_MAX;
	get_focus(u, -1, sz[u], u, x);
	flag[u] = true;
	ch[u] = fa;
	dep[u] = 0;
	calc_dep(u, -1);
	calc_ans(u, p[u], true);
	for (int i = 0; i < g[u].size(); i++)
		if (!flag[e[g[u][i]]]) calc_ans(e[g[u][i]], c[g[u][i]], false);
	for (int i = 0; i < g[u].size(); i++)
	{
		int v = e[g[u][i]];
		if (!flag[v]) solve(v, g[u][i]);
	}
}

long long update(int u, int val)
{
	long long ret = 0;
	for (int i = f[u].size() - 1; i >= 0; i--)
	{
		int an = f[u][i].first;
		long long dis = f[u][i].second;
		for (int j = 0; j < M; j++)
		{
			int x = (A[u] & (1 << j)) > 0, y = (val & (1 << j)) > 0;
			ret -= (p[an][j].dis[x ^ 1] + p[an][j].cnt[x ^ 1] * dis) << j;
			p[an][j].dis[x] -= dis;
			p[an][j].cnt[x]--;
			ret += (p[an][j].dis[y ^ 1] + p[an][j].cnt[y ^ 1] * dis) << j;
			p[an][j].dis[y] += dis;
			p[an][j].cnt[y]++;
			if (i < f[u].size() - 1)
			{
				int anc = ch[f[u][i + 1].first];
				ret += (c[anc][j].dis[x ^ 1] + c[anc][j].cnt[x ^ 1] * dis) << j;
				c[anc][j].dis[x] -= dis;
				c[anc][j].cnt[x]--;
				ret -= (c[anc][j].dis[y ^ 1] + c[anc][j].cnt[y ^ 1] * dis) << j;
				c[anc][j].dis[y] += dis;
				c[anc][j].cnt[y]++;
			}
		}
	}
	A[u] = val;
	return ret;
}

bool read(int n, ...)
{
	va_list li;
	va_start(li, n);
	for (int i = 0; i < n; i++)
	{
		int &x = *va_arg(li, int *);
		x = 0;
		int ch;
		do ch = getchar();
		while (ch != EOF && !isdigit(ch));
		if (ch == EOF) return false;
		do
		{
			(x *= 10) += ch - '0';
			ch = getchar();
		} while (ch != EOF && isdigit(ch));
		if (ch == EOF) return false;
	}
	va_end(li);
	return true;
}

int main()
{
	int n;
	while (read(1, &n))
	{
		memset(flag, 0x00, sizeof flag);
		memset(A, 0x00, sizeof A);
		for (int i = 0; i < n; i++)
		{
			g[i].clear();
			f[i].clear();
			memset(p[i], 0x00, sizeof p[i]);
			memset(c[i], 0x00, sizeof c[i]);
			memset(c[i + n], 0x00, sizeof c[i + n]);
		}
		e.clear();
		for (int i = 0; i < n; i++) read(1, &a[i]);
		for (int i = 0; i < n - 1; i++)
		{
			int a, b, c;
			read(3, &a, &b, &c);
			a--;
			b--;
			g[a].push_back(e.size());
			len[e.size()] = c;
			e.push_back(b);
			g[b].push_back(e.size());
			len[e.size()] = c;
			e.push_back(a);
		}
		solve(0, -1);
		long long ans = 0;
		for (int i = 0; i < n; i++) ans += update(i, a[i]);
		int t;
		read(1, &t);
		for (int i = 0; i < t; i++)
		{
			int d, e;
			read(2, &d, &e);
			ans += update(d - 1, e);
			printf("%lld\n", ans);
		}
	}
}

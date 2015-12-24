#include <cstdio>
#include <algorithm>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdarg>
#include <cctype>
#include <cstring>
#include <map>
using namespace std;
const int N = 10000;
vector<int> g[N];
bool flag[N];
int sz[N], phi[N + 1];
long long ct[N + 1], sg[N], depw[N];
void get_nodes(int u, int fa, vector<int> &vi)
{
	vi.push_back(u);
	for (int i = 0; i < g[u].size(); i++)
	{
		int v = g[u][i];
		if (v != fa && !flag[v])
			get_nodes(v, u, vi);
	}
}
void calc_size(int u, int fa)
{
	sz[u] = 1;
	for (int i = 0; i < g[u].size(); i++)
	{
		int v = g[u][i];
		if (v != fa && !flag[v])
		{
			calc_size(v, u);
			sz[u] += sz[v];
		}
	}
}
void calc_depw(int u, int fa)
{
	for (int i = 0; i < g[u].size(); i++)
	{
		int v = g[u][i];
		if (v != fa && !flag[v])
		{
			depw[v] = depw[u] ^ sg[v];
			calc_depw(v, u);
		}
	}
}
void get_focus(int u, int fa, int n, int &ans, int &min)
{
	int max = n - sz[u];
	for (int i = 0; i < g[u].size(); i++)
	{
		int v = g[u][i];
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
int calc_ans(int u)
{

	map<long long, int> m;
	int ans = 0;
	if (sg[u] == 0) ans++;
	for (int i = 0; i < g[u].size(); i++)
	{
		int v = g[u][i];
		if (flag[g[u][i]]) continue;
		vector<int> vi;
		get_nodes(v, -1, vi);
		depw[v] = sg[v];
		calc_depw(v, -1);
		for (int j = 0; j < vi.size(); j++)
		{
			ans += (m[sg[u] ^ depw[vi[j]]]) * 2;
			if ((sg[u] ^ depw[vi[j]]) == 0) ans += 2;
		}
		for (int j = 0; j < vi.size(); j++) m[depw[vi[j]]]++;
	}
	return ans;
}
int solve(int u)
{
	calc_size(u, -1);
	int x = INT_MAX;
	get_focus(u, -1, sz[u], u, x);
	flag[u] = true;
	calc_size(u, -1);
	depw[u] = 0;
	calc_depw(u, -1);
	int ans = calc_ans(u);
	for (int i = 0; i < g[u].size(); i++)
		if (!flag[g[u][i]]) ans += solve(g[u][i]);
	return ans;
}
long long get(int n, int m)
{
	long long res = 0;
	if (n > m) swap(n, m);
	for (int i = 1, j; i <= n; i = j + 1)
	{
		j = min(n / (n / i), m / (m / i));
		res += (long long)(phi[j] - phi[i - 1]) * (n / i) * (m / i);
	}
	return res;
}
int gcd(int a, int b)
{
	return b == 0 ? a : gcd(b, a%b);
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
	for (int i = 0; i <= N; i++) phi[i] = i;
	for (int i = 2; i <= N; i++)
		if (phi[i] == i)
			for (int j = i; j <= N; j += i)
				phi[j] = phi[j] / i * (i - 1);
	for (int i = 2; i <= N; i++) phi[i] += phi[i - 1];
	for (int i = 1; i <= N; i++)
		ct[i] = get(i, i) + ct[i - 1];
	int n;
	while (read(1, &n))
	{
		memset(flag, 0x00, sizeof flag);
		for (int i = 0; i < n; i++) g[i].clear();
		for (int i = 0; i < n - 1; i++)
		{
			int a, b;
			read(2, &a, &b);
			g[a - 1].push_back(b - 1);
			g[b - 1].push_back(a - 1);
		}
		for (int i = 0; i < n; i++)
		{
			int t, a, b, c;
			read(4, &t, &a, &b, &c);
			sg[i] = ct[t - 1] + c - 1;
			sg[i] += get(a - 1, t);
			sg[i] += get(a, b - 1) - get(a - 1, b - 1);
		}
		int ans = n*n - solve(0);
		int x = gcd(ans, n*n);
		printf("%d/%d\n", ans / x, n*n / x);
	}
}
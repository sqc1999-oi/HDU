#include <cstdio>
#include <cstdarg>
#include <cctype>
#include <algorithm>
using namespace std;
void read(int n, ...)
{
	va_list li;
	va_start(li, n);
	while (n--)
	{
		int &x = *va_arg(li, int *), ch;
		x = 0;
		do ch = getchar();
		while (!isdigit(ch));
		do
		{
			x = x * 10 + ch - '0';
			ch = getchar();
		} while (isdigit(ch));
	}
	va_end(li);
}
const int N = 5e4;
struct q
{
	int id, x, y, z, t;
	q(int id, int x, int y, int z, int t) :id(id), x(x), y(y), z(z), t(t) {}
	q() {}
} a[N * 8], b[N * 8];
int ans[N], t[N * 2];
namespace bit
{
	int t[N * 2 + 1];
	int lowbit(int x) { return x&-x; }
	void update(int k, int x) { for (; k <= N * 2; k += lowbit(k)) t[k] += x; }
	int query(int k)
	{
		int ans = 0;
		for (; k > 0; k -= lowbit(k)) ans += t[k];
		return ans;
	}
}
bool cmp_z_id(const q &a, const q &b) { return a.z < b.z || a.z == b.z&&a.id < b.id; }
bool cmp_y(const q &a, const q &b) { return a.y < b.y; }
void cdq(int l, int r)
{
	if (l >= r - 1) return;
	int mid = (l + r) / 2;
	cdq(l, mid);
	cdq(mid, r);
	int j = l;
	for (int i = mid; i < r; i++)
	{
		for (; j < mid&&b[j].y <= b[i].y; j++)
			if (b[j].t == 0) bit::update(b[j].x, 1);
		if (b[i].t != 0) ans[b[i].id] += b[i].t*bit::query(b[i].x);
	}
	for (int i = l; i < j; i++)
		if (b[i].t == 0) bit::update(b[i].x, -1);
	inplace_merge(b + l, b + mid, b + r, cmp_y);
}
void divide(int l, int r)
{
	if (l >= r - 1) return;
	int mid = (l + r) / 2;
	divide(l, mid);
	divide(mid, r);
	int cnt = 0;
	for (int i = l; i < mid; i++)
		if (a[i].t == 0) b[cnt++] = a[i];
	for (int i = mid; i < r; i++)
		if (a[i].t != 0) b[cnt++] = a[i];
	sort(b, b + cnt, cmp_z_id);
	cdq(0, cnt);
}
int main()
{
	int T;
	read(1, &T);
	while (T--)
	{
		int n, cnt = 0, xcnt = 0;
		read(1, &n);
		for (int i = 0; i < n; i++)
		{
			int t;
			read(1, &t);
			if (t == 1)
			{
				read(3, &a[cnt].x, &a[cnt].y, &a[cnt].z);
				a[cnt].t = 0;
				a[cnt].id = i;
				::t[xcnt++] = a[cnt].x;
				cnt++;
				ans[i] = -1;
			}
			else if (t == 2)
			{
				int x1, y1, z1, x2, y2, z2;
				read(6, &x1, &y1, &z1, &x2, &y2, &z2);
				a[cnt++] = q(i, x2, y2, z2, 1);
				a[cnt++] = q(i, x1 - 1, y2, z2, -1);
				a[cnt++] = q(i, x2, y1 - 1, z2, -1);
				a[cnt++] = q(i, x2, y2, z1 - 1, -1);
				a[cnt++] = q(i, x1 - 1, y1 - 1, z2, 1);
				a[cnt++] = q(i, x1 - 1, y2, z1 - 1, 1);
				a[cnt++] = q(i, x2, y1 - 1, z1 - 1, 1);
				a[cnt++] = q(i, x1 - 1, y1 - 1, z1 - 1, -1);
				::t[xcnt++] = x1 - 1;
				::t[xcnt++] = x2;
				ans[i] = 0;
			}
		}
		sort(t, t + xcnt);
		xcnt = unique(t, t + xcnt) - t;
		for (int i = 0; i < cnt; i++)
			a[i].x = lower_bound(t, t + xcnt, a[i].x) - t + 1;
		divide(0, cnt);
		for (int i = 0; i < n; i++)
			if (ans[i] != -1) printf("%d\n", ans[i]);
	}
}

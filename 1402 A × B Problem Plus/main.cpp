#include <iostream>
#include <algorithm>
#include <complex>
#include <cmath>
#include <cstring>
using namespace std;
typedef complex<double> cmplx;
const double PI = acos(-1.0);
cmplx a[200000], b[200000];
int res[200000];
int rev(int x, int n)
{
	int res = 0;
	for (int i = 0; i < n; i++)
	{
		res <<= 1;
		res |= x & 1;
		x >>= 1;
	}
	return res;
}
void dft(cmplx *a, int n, int flag)
{
	static cmplx tmp[200000];
	int lg = round(log2(n));
	for (int i = 0; i < n; i++)
		tmp[rev(i, lg)] = a[i];
	for (int i = 0, j = 2; i < lg; i++, j <<= 1)
	{
		cmplx wm(cos(flag * 2 * PI / j), sin(flag * 2 * PI / j));
		for (int k = 0; k < n; k += j)
		{
			cmplx w = 1;
			for (int l = 0; l < j / 2; l++)
			{
				cmplx u = w*tmp[k + l + j / 2], t = tmp[k + l];
				tmp[k + l] = t + u;
				tmp[k + l + j / 2] = t - u;
				w *= wm;
			}
		}
	}
	if (flag == -1)	for (int i = 0; i < n; i++) tmp[i] /= n;
	for (int i = 0; i < n; i++) a[i] = tmp[i];
}
int main()
{
	ios::sync_with_stdio(false);
	string s1, s2;
	while (cin >> s1 >> s2)
	{
		memset(a, 0x00, sizeof a);
		memset(b, 0x00, sizeof b);
		for (int i = s1.length() - 1, j = 0; i >= 0; i--, j++)
			a[j] = s1[i] - '0';
		for (int i = s2.length() - 1, j = 0; i >= 0; i--, j++)
			b[j] = s2[i] - '0';
		int n = 1;
		while (n < s1.length() * 2 || n < s2.length() * 2) n <<= 1;
		dft(a, n, 1);
		dft(b, n, 1);
		for (int i = 0; i < n; i++) a[i] *= b[i];
		dft(a, n, -1);
		for (int i = 0; i < n; i++) res[i] = round(a[i].real());
		for (int i = 0; i < n - 1; i++)
		{
			res[i + 1] += res[i] / 10;
			res[i] %= 10;
		}
		int x = n - 1;
		while (x > 0 && res[x] == 0) x--;
		for (int i = x; i >= 0; i--) cout << res[i];
		cout << endl;
	}
}

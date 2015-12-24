#include <iostream>
#include <algorithm>
#include <complex>
#include <string>
#include <cmath>
using namespace std;
typedef complex<double> cmplx;
const double PI = acos(-1.0);
int res[200000];
cmplx a[200000], b[200000], c[200000], d[200000];
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
void dft(cmplx *a, cmplx *b, int n, int flag)
{
	int lg = round(log2(n));
	for (int i = 0; i < n; i++)
		b[rev(i, lg)] = a[i];
	for (int i = 1, j = 2; i <= lg; i++, j <<= 1)
	{
		cmplx wm(cos(2 * PI / j*flag), sin(2 * PI / j*flag));
		for (int k = 0; k < n; k += j)
		{
			cmplx w = 1;
			for (int l = 0; l < j / 2; l++)
			{
				cmplx t = w * b[k + l + j / 2], u = b[k + l];
				b[k + l] = u + t;
				b[k + l + j / 2] = u - t;
				w *= wm;
			}
		}
	}
	if (flag == -1)
		for (int i = 0; i < n; i++)
			b[i] /= n;
}
int main()
{
	ios::sync_with_stdio(false);
	string s1, s2;
	while (cin >> s1 >> s2)
	{
		for (int i = 0, j = s1.length() - 1; i < s1.length(); i++, j--)
			a[i] = s1[j] - '0';
		for (int i = 0, j = s2.length() - 1; i < s2.length(); i++, j--)
			b[i] = s2[j] - '0';
		int n = 1;
		while (n < s1.length() * 2 || n < s2.length() * 2) n <<= 1;
		dft(a, c, n, 1);
		dft(b, d, n, 1);
		for (int i = 0; i < n; i++)
			c[i] *= d[i];
		dft(c, a, n, -1);
		for (int i = 0; i < n; i++) res[i] = int(round(a[i].real()));
		for (int i = 0; i < n - 1; i++)
		{
			res[i + 1] += res[i] / 10;
			res[i] %= 10;
		}
		int x = n - 1;
		while (x > 0 && res[x] == 0) x--;
		for (int i = x; i >= 0; i--) cout << char(res[i] + '0');
		cout << endl;
	}
}

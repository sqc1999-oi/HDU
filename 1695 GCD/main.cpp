#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

const int MAXN = 10000;
int prime[MAXN + 1];
void getPrime()
{
	memset(prime, 0, sizeof(prime));
	for (int i = 2; i <= MAXN; i++)
	{
		if (!prime[i])prime[++prime[0]] = i;
		for (int j = 1; j <= prime[0] && prime[j] <= MAXN / i; j++)
		{
			prime[prime[j] * i] = 1;
			if (i%prime[j] == 0)break;
		}
	}
}
long long factor[100][2];
int fatCnt;
int getFactors(long long x)
{
	fatCnt = 0;
	long long tmp = x;
	for (int i = 1; prime[i] <= tmp / prime[i]; i++)
	{
		factor[fatCnt][1] = 0;
		if (tmp%prime[i] == 0)
		{
			factor[fatCnt][0] = prime[i];
			while (tmp%prime[i] == 0)
			{
				factor[fatCnt][1]++;
				tmp /= prime[i];
			}
			fatCnt++;
		}
	}
	if (tmp != 1)
	{
		factor[fatCnt][0] = tmp;
		factor[fatCnt++][1] = 1;
	}
	return fatCnt;
}
int euler[100010];
void getEuler()
{
	memset(euler, 0, sizeof(euler));
	euler[1] = 1;
	for (int i = 2; i <= 100000; i++)
		if (!euler[i])
			for (int j = i; j <= 100000; j += i)
			{
				if (!euler[j])
					euler[j] = j;
				euler[j] = euler[j] / i*(i - 1);
			}
}
int calc(int n, int m)
{
	getFactors(m);
	int ans = 0;
	for (int i = 1; i < (1 << fatCnt); i++)
	{
		int cnt = 0;
		int tmp = 1;
		for (int j = 0; j < fatCnt; j++)
			if (i&(1 << j))
			{
				cnt++;
				tmp *= factor[j][0];
			}
		if (cnt & 1)ans += n / tmp;
		else ans -= n / tmp;
	}
	return n - ans;
}
int main()
{
	getPrime();
	int a, b, c, d;
	int T;
	int k;
	scanf("%d", &T);
	int iCase = 0;
	getEuler();
	while (T--)
	{
		iCase++;
		scanf("%d%d%d%d%d", &a, &b, &c, &d, &k);
		if (k == 0 || k > b || k > d)
		{
			printf("Case %d: 0\n", iCase);
			continue;
		}
		if (b > d)swap(b, d);
		b /= k;
		d /= k;
		long long ans = 0;
		for (int i = 1; i <= b; i++)
			ans += euler[i];
		for (int i = b + 1; i <= d; i++)
			ans += calc(b, i);
		printf("Case %d: %I64d\n", iCase, ans);
	}

	return 0;
}

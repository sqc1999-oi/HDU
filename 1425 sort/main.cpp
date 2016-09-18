#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

int main()
{
	int n, m;
	while (~scanf("%d%d", &n, &m))
	{
		priority_queue<int> q;
		for (int i = 1; i <= n; i++)
		{
			int x;
			scanf("%d", &x);
			q.push(x);
		}
		for (int i = 1; i < m; i++)
			printf("%d ", q.top()) , q.pop();
		printf("%d\n", q.top());
	}
}

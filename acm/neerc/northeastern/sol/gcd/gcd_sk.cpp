/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <cstdio>
#include <cassert>

const int maxN = 10000;

int n, pn, p[maxN + 1];

int main()
{
  assert(freopen("gcd.in", "r", stdin));
  assert(freopen("gcd.out", "w", stdout));

  assert(scanf("%d", &n) == 1);
  assert(1 <= n && n <= maxN);

  for (int i = 2; i <= n; i++)
    if (!p[i])
    {
      p[pn++] = i;
      for (int j = i + i; j <= n; j += i)
        p[j] = 1;
    }

  int i = 0, j = pn - 1, cnt = 0;
  while (i <= j)
  {
    int x = p[j--];
    if (i <= j && p[i] <= n / x)
      x *= p[i++];
    cnt++;
  }
  printf("%d\n", cnt);
  return 0;
}

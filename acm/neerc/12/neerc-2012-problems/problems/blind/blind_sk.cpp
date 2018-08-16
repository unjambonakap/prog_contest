/******************************************************************/
/* ACM ICPC 2012-2013                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tashkent - Tbilisi, December 2, 2012 */
/******************************************************************/
/* Problem B. Blind Problem Solving                               */
/*                                                                */
/* Original idea         Maxim Buzdalov                           */
/* Problem statement     Maxim Buzdalov                           */
/* Test set              Maxim Buzdalov                           */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author                Sergey Kopeliovich                       */
/******************************************************************/

/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2012.11.21
 */

#include <cstdio>
#include <cassert>
#include <set>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int maxN = 20;
const int maxC = (int)1e9;
const int maxW = (int)1e8;

int n, c, m, m1, f = 1;
int res = 0, an, a[maxN], w[1 << maxN];
multiset <int> diff;

void move()
{
  puts(f ? "accept" : "decline"), fflush(stdout);
  scanf("%d", &m1), f = 0;
}

int main()
{
  scanf("%d%d%d", &n, &c, &m);
  assert(1 <= n && n <= maxN);
  assert(0 <= c && c <= maxC);
  
  while (m > 0)
  {
    move();
    if (m1 < m)
      f = 1, m = m1;
  }
  while (an < n)
  {
    move();
    if (m1 > m)
      f = 1, a[an++] = m1 - m, m = m1;
  }
  
  forn(i, 1 << n)
  {
    forn(j, n)
      if ((i >> j) & 1)
        w[i] += a[j];
    if (w[i] <= c && w[i] > w[res])
      res = i;
  }
  forn(j, n)
    if (!((res >> j) & 1))
      diff.insert(a[j]);

  while (m > w[res])
  {
    move();
    if (diff.count(m - m1))
      f = 1, diff.erase(diff.find(m - m1)), m = m1;
  }
  puts("stop"), fflush(stdout);
  return 0;
}


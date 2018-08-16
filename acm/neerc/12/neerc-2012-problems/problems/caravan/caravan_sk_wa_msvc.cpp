/******************************************************************/
/* ACM ICPC 2012-2013                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tashkent - Tbilisi, December 2, 2012 */
/******************************************************************/
/* Problem C. Caravan Robbers                                     */
/*                                                                */
/* Original idea         Egor Kulikov                             */
/* Problem statement     Egor Kulikov                             */
/* Test set              Egor Kulikov                             */
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
#include <algorithm>
#include <cmath>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define mp make_pair

typedef long double dbl;

const int maxN = (int)1e5;
const int maxC = (int)1e6;
const dbl eps = 3e-6;

int n, a[maxN], b[maxN], p[maxN];

bool pless( int i, int j )
{
  #define F(i) mp(a[i], b[i])
  return F(i) < F(j);
}

bool is_int( dbl x )
{
  int val = (int)(x + 0.5);
  x -= val;
  return fabs(x) < eps;
}

int main()
{
  #define NAME "caravan"
  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));

  assert(scanf("%d", &n) == 1);
  assert(1 <= n && n <= maxN);
  forn(i, n)
  {
    assert(scanf("%d%d", &a[i], &b[i]) == 2);
    assert(0 <= a[i] && a[i] < b[i] && b[i] <= maxC);
    p[i] = i;
  }
  sort(p, p + n, pless);
  forn(i, n - 1)
    assert(b[p[i]] <= b[p[i + 1]]);

  dbl l = 0, r = maxC;
  forn(_, 100)
  {
    dbl m = (l + r) / 2, pos = 0;
    int bad = 0;
    forn(_i, n)
    {
      int i = p[_i];
      if (pos < a[i])
        pos = a[i];
      if (pos + m > b[i])
        bad = 1;
      pos += m;
    }

    if (!bad)
      l = m;
    else
      r = m;
  }
  fprintf(stderr, "l = %.20f\n", l);

  int q = 1;
  while (!is_int(l * q))
    q++;
  printf("%.0f/%d\n", (double)(l * q), q);
  return 0;
}


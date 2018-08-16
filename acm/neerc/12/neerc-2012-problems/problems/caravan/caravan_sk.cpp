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
const dbl eps = 1e-6;

int gcd( int a, int b ) { return b ? gcd(b, a % b) : a; }

int n, a[maxN], b[maxN], p[maxN];

bool pless( int i, int j )
{
  #define F(i) mp(a[i], b[i])
  return F(i) < F(j);
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
  fprintf(stderr, "l = %.20f\n", (double)l);

  int rq = 0;
  dbl min_diff = 1e100;
  for (int q = 1; q <= n; q++)
  {
    dbl pr = l * q;
    int val = (int)(pr + 0.5);
    dbl diff = fabs(pr - val) / q;
    if (diff < min_diff)
      min_diff = diff, rq = q;
  }
  fprintf(stderr, "min_diff = %.20f\n", (double)min_diff);

  int rp = (int)(l * rq + 0.5);
  int g = gcd(rp, rq);
  printf("%d/%d\n", rp / g, rq / g);
  return 0;
}


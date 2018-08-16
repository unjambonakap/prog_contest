/******************************************************************/
/* ACM ICPC 2012-2013                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tashkent - Tbilisi, December 2, 2012 */
/******************************************************************/
/* Problem A. Addictive Bubbles                                   */
/*                                                                */
/* Original idea         Georgiy Korneev                          */
/* Problem statement     Georgiy Korneev                          */
/* Test set              Georgiy Korneev                          */
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

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int maxN = 10;

char s[maxN][maxN + 1];

int main()
{
  #define NAME "addictive"
  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));

  int h, w, c, a, x = 0, y = 0; 
  assert(scanf("%d%d%d", &h, &w, &c) == 3);
  assert(1 <= h && h <= maxN && 1 <= w && w <= maxN && 1 <= c && c <= 9);
  forn(i, c)
  {
    scanf("%d", &a);
    while (a--)
    {
      s[(x & 1) ? y : (h - y - 1)][x] = '1' + i;
      if (++y == h)
        x++, y = 0;
    }
  }
  forn(i, h)
    puts(s[i]);
  return 0;
}


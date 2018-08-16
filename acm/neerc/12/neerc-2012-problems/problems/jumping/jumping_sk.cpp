/******************************************************************/
/* ACM ICPC 2012-2013                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tashkent - Tbilisi, December 2, 2012 */
/******************************************************************/
/* Problem J. Jumping Around                                      */
/*                                                                */
/* Original idea         Andrey Stankevich                        */
/* Problem statement     Andrey Stankevich                        */
/* Test set              Andrey Stankevich                        */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author                Sergey Kopeliovich                       */
/******************************************************************/

/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2012.11.22
 */

#include <cstdio>
#include <cassert>
#include <algorithm>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int maxT = 20;
const int maxA = 5000;

int p, a, b, c, n, x, tn, f;

void add( int x )
{
  (abs(x) == 1 ? a : (abs(x) == 2 ? b : c))--;
  printf("%d ", p += x);
}

int main()
{
  #define NAME "jumping"
  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));
  
  assert(scanf("%d", &tn) == 1);
  assert(1 <= tn && tn <= maxT);
  while (tn--)
  {
    assert(scanf("%d%d%d", &a, &b, &c) == 3);
    assert(3 <= a && a <= maxA);
    assert(3 <= b && b <= maxA);
    assert(3 <= c && c <= maxA);

    n = a + b + c + 1, x = c / 3, p = 0;
    printf("%d ", p);
    if (c % 3 == 0)
    {
      forn(i, x)
        add(3);
      add(1);
      forn(i, x)
        add(-3);
      add(1);
      forn(i, x)
        add(3);
    }
    else if (c % 3 == 1)
    {
      forn(i, x + 1)
        add(3);
      add(-2);
      forn(i, x)
        add(-3);
      add(1);
      forn(i, x)
        add(3);
      add(2);
    }
    else if (c % 3 == 2)
    {
      forn(i, x + 1)
        add(3);
      add(-2);
      forn(i, x)
        add(-3);
      add(1);
      forn(i, x + 1)
        add(3);
      add(-1);
      add(2);
    }
    f = b & 1, x = b / 2;
    while (a > 1)
      add(1);
    while (b > x)
      add(2);
    add(f ? -1 : 1);
    forn(i, x)
      add(-2);
    puts("");
  }
  return 0;
}


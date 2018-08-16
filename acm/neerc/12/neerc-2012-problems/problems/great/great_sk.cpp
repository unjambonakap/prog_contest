/******************************************************************/
/* ACM ICPC 2012-2013                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tashkent - Tbilisi, December 2, 2012 */
/******************************************************************/
/* Problem G. Great Deceiver                                      */
/*                                                                */
/* Original idea         Elana Kryuchkova                         */
/* Problem statement     Dmitry Gozman                            */
/* Test set              Dmitry Gozman                            */
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
#include <iostream>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

const ll maxN = (ll)1e15;
const int maxK = 1000;
const int maxL = 64;

int k, l;
ll n, x[maxL];

int main()
{
  #define NAME "great"
  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));
  
  assert(cin >> n >> k);
  assert(1 <= n && n <= maxN && 2 <= k && k <= maxK);

  assert((ll)((1ULL << 63) - 1) / maxK >= maxN); // no overflow

  x[0] = 1, l = 1;
  while ((x[l] = (x[l - 1] * k)) <= n)
    l++;

  ll sum = 0;
  for (l--, l -= l & 1; l >= 0; l -= 2)
    if (n >= x[l] * k)
    {
      sum += x[l / 2 + 1];
      break;
    }
    else
    {
      int d = n / x[l];
      sum += x[l / 2] * (d + (l == 0));
      n -= x[l] * d;
    }
  cout << sum << endl;
  return 0;
}


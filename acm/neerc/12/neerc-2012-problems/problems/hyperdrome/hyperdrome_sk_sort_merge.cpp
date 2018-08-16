/******************************************************************/
/* ACM ICPC 2012-2013                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tashkent - Tbilisi, December 2, 2012 */
/******************************************************************/
/* Problem H. Hyperdrome                                          */
/*                                                                */
/* Original idea         Vitaliy Aksenov                          */
/* Problem statement     Vitaliy Aksenov                          */
/* Test set              Vitaliy Aksenov                          */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author                Sergey Kopeliovich                       */
/******************************************************************/

/**                   
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2012.11.23
 */

#include <cstdio>
#include <cstring>
#include <cassert>

#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef unsigned long long ll;

const int maxN = (int)3e5 + 2;
const int E = 52;

int n;
ll h[maxN], h1[maxN];
ll x = 0, res = 0;

int main()
{
  #define NAME "hyperdrome"
  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));
  
  assert(scanf("%d ", &n) == 1);
  assert(1 <= n && n <= maxN);

  forn(i, n)
  {
    char c;
    assert(scanf("%c", &c) == 1);
    int a = ('a' <= c && c <= 'z') ? c - 'a' : (('A' <= c && c <= 'Z') ? c - 'A' + 26 : -1);
    assert(0 <= a && a < E);
    h[i] = x, x ^= 1LL << a;
  }
  h[n++] = x;
  sort(h, h + n);

  h[n] = (ll)-1;
  for (int j, i = 0; i < n; i = j)
  {
    for (j = i; h[i] == h[j]; j++)
      ;
    res += (ll)(j - i) * (j - i - 1);
  }

  forn(k, E)
  {
    ll bit = 1LL << k;
    for (int pos, r, l = 0; l < n; l = r)
    {
      ll base = h[l] & ~(ll)((bit << 1) - 1);
      for (r = l; h[r] < base + bit; r++)
        ;
      pos = r;
      for (r = l; h[r] < base + (bit << 1); r++)
        ;

      int k = 0;
      for (int i = pos; i < r; i++)
        h1[k++] = h[i] ^ bit;
      for (int i = l; i < pos; i++)
        h1[k++] = h[i] ^ bit;
      h1[k] = (ll)-1;

      pos = 0;
      for (int j, i = l; i < r; i = j)
      {
        for (j = i; h[i] == h[j]; j++)
          ;
        while (h1[pos] < h[i])
          pos++;
        while (h1[pos] == h[i])
          pos++, res += j - i;
      }
    }
  }
  cout << res / 2 << endl;
  return 0;
}


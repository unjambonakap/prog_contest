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

#define KOEF 2

const int maxN = (int)3e5;
const int E = 52;
const int maxH = maxN * KOEF + 3;

int n, a[maxN];
ll h[maxH], t[maxN + 1];
int hf[maxH];
ll x = 0, res = 0;
int cnt1 = 0, cnt2 = 0, cnt3 = 0;

inline int get_i( ll hash )
{
  hash += 13;
  cnt1++;
  int i = hash % maxH;
  while (h[i] && h[i] != hash)
  {
    cnt3++;
    if (++i == maxH)
      i = 0;
  }
  return i;
}

int &get( ll hash )
{
  int i = get_i(hash);
  if (!h[i])
    cnt2++, h[i] = hash + 13;
  return hf[i];
}

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
    a[i] = ('a' <= c && c <= 'z') ? c - 'a' : (('A' <= c && c <= 'Z') ? c - 'A' + 26 : -1);
    assert(0 <= a[i] && a[i] < E);
  }

  forn(r, n)
    res += get(t[r] = x)++, x ^= 1LL << a[r];
  res += get(t[n] = x)++;

  forn(r, n + 1)
  {
    ll x = t[r];
    forn(i, E)
    {
      ll b = 1LL << i;
      if (!(x & b))
        res += hf[get_i(x ^ b)];
    }
  }

  fprintf(stderr, "call get: %d\n", cnt1);
  fprintf(stderr, "overhead: %d\n", cnt3);
  fprintf(stderr, "size:     %d\n", cnt2);

  cout << res << endl;
  return 0;
}


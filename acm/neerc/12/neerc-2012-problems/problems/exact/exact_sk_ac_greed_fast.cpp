/******************************************************************/
/* ACM ICPC 2012-2013                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tashkent - Tbilisi, December 2, 2012 */
/******************************************************************/
/* Problem E. Exact Measurement                                   */
/*                                                                */
/* Original idea         Pavel Mavrin                             */
/* Problem statement     Pavel Mavrin                             */
/* Test set              Pavel Mavrin                             */
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
#include <vector>

#define DEBUG 0

#ifdef _WIN32
#  define I64 "%I64d"
#else
#  define I64 "%lld"
#endif

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define pb push_back
#define mp make_pair
#define sz(a) (int)(a).size()

typedef long long ll;

const int maxN = (int)1e5;
const int maxK = 18;

ll x, deg[maxK + 1], len[maxN];
int rn, n, pos[maxK + 1];
vector <int> id[maxK + 1];
vector <ll> slen[maxK + 1];

bool lless( int i, int j ) { return len[i] > len[j]; }

ll GetX()
{
  ll rest = x;
  for (int i = maxK; i >= 0; i--)
  {
    ll sum = slen[i][pos[i]];
    if (rest > sum)
      rest -= sum;
    else
      rest = rest % deg[i];
  }
  return rest;
}

int main()
{
  #define NAME "exact"
  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));

  deg[0] = 1;
  forn(i, maxK)
    deg[i + 1] = deg[i] * 10;

  scanf(I64"%d", &x, &n); 
  assert(1 <= x && x <= (ll)1e18);
  assert(1 <= n && n <= maxN);
  forn(i, n)
  {
    int k;
    ll l;
    scanf("%d"I64, &k, &l);
    assert(0 <= k && k <= maxK);
    assert(1 <= l && l <= deg[maxK - k]);
    len[i] = l * deg[k];
    id[k].pb(i);
  }
  forn(i, maxK + 1)
  {
    ll sum = 0;
    sort(id[i].begin(), id[i].end(), lless);
    slen[i].pb(sum);
    forn(j, sz(id[i]))
      slen[i].pb(sum += len[id[i][j]]);
    pos[i] = 0;
  }

  while (GetX() > 0)
  {
    int ri = -1;
    ll t, rt = GetX();
    for (int i = maxK; i >= 0; i--)
      if (pos[i] < sz(id[i]))
      {
        pos[i]++;
        if ((t = GetX()) < rt)
          rt = t, ri = i;
        pos[i]--;
      }
    if (ri == -1)
    {
      puts("-1");
      return 0;
    }
    pos[ri]++, rn++;
  }
  printf("%d\n", rn);
  forn(i, maxK + 1)
    forn(j, pos[i])
      printf("%d ", id[i][j] + 1);
  return 0;
}


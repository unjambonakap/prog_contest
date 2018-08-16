/******************************************************************/
/* ACM ICPC 2012-2013                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tashkent - Tbilisi, December 2, 2012 */
/******************************************************************/
/* Problem I. Identification of Protein                           */
/*                                                                */
/* Original idea         Mikhail Dvorkin                          */
/* Problem statement     Mikhail Dvorkin                          */
/* Test set              Mikhail Dvorkin                          */
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
#include <cstring>
#include <cassert>
#include <cmath>
#include <algorithm>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define mp make_pair

typedef long long ll;

const int maxN = (int)1e5;
const int maxL = 500;
const int maxD = 250;
const int maxD1 = maxD + 1;

const ll P = 9705276;
const ll Q = 12805858;

int n;
ll x, y, mass, len, plen, qlen, a[maxN];
int bonus[maxD1][maxD1];
int f[maxD1][maxD1][maxD1];
int last_i[maxD1][maxD1][maxD1];
int last_j[maxD1][maxD1][maxD1];

int n1, n2;
char s1[maxL], s2[maxL];

// Solve equation xP + yQ == mass
bool get( ll mass, ll &x, ll &y )
{ 
  ll x1 = 1, y1 = 0, a1 = P;
  ll x2 = 0, y2 = 1, a2 = Q;
  while (a2)
  {
    ll k = a1 / a2;
    ll x3 = x1 - x2 * k;
    ll y3 = y1 - y2 * k;
    ll a3 = a1 - a2 * k;
    x1 = x2, y1 = y2, a1 = a2;
    x2 = x3, y2 = y3, a2 = a3;
  }
  if (mass % a1 != 0)
    return 0;

  ll k = mass / a1, dx = P / a1, dy = Q / a1;
  x = x1 * k, y = y1 * k;
  assert(x * P + y * Q == mass);
  if (x < 0) k = (-x + dy - 1) / dy, x += k * dy, y -= k * dx;
  if (y < 0) k = (-y + dx - 1) / dx, x -= k * dy, y += k * dx;
  if (x < 0) return 0;
  assert(x >= 0 && y >= 0 && x * P + y * Q == mass);
  return 1;
}

void add_res( int f, char *s, int &sn )
{
  s[sn++] = f ? 'P' : 'Q';
}

void relax( int k, int pi, int pj, int i, int j )
{
  int F = f[k - 1][i][j] + bonus[pi][k - pi] + (pi != pj) * bonus[pj][k - pj];
  if (f[k][pi][pj] < F)
    f[k][pi][pj] = F, last_i[k][pi][pj] = i, last_j[k][pi][pj] = j;
}

int main()
{
  #define NAME "identification"
  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));
  
  assert(scanf("%d", &n) == 1);
  assert(1 <= n && n <= maxN);
  forn(i, n)
  {
    double x;
    assert(scanf("%lf", &x) == 1);
    a[i] = (ll)(x * 1e5 + 0.5);
    assert(fabs(a[i] - x * 1e5) < 1e-6);
  }
  
  assert(get(mass = *max_element(a, a + n), plen, qlen));
  len = plen + qlen;
  assert(1 <= len && len <= maxL);

  ll x, y;
  forn(i, n)
    if (get(a[i], x, y) && x <= plen && y <= qlen)
    {
      if ((x + y) * 2 > len)
        x = plen - x, y = qlen - y;
      assert(x <= maxD && y <= maxD);
      bonus[x][y]++;
    }

  int l = len / 2, ri = 0, rj = 0;
  f[0][0][0] = 1;
  forn(k, l + 1)
    forn(pi, k + 1)
      forn(pj, pi + 1)
        if (k < l)
          forn(di, 2)
            forn(dj, 2)
              relax(k + 1, pi + di, pj + dj, pi, pj);
        else if (f[k][pi][pj] > f[k][ri][rj] && pi + pj <= plen && 2 * k - pi - pj <= qlen)
          ri = pi, rj = pj;
  fprintf(stderr, "%d\n", f[l][ri][rj] - 1);        

  if (len & 1)
    add_res(plen - ri - rj, s1, n1);
  for (int k = l; k > 0; k--)
  {
    int i = last_i[k][ri][rj];
    int j = last_j[k][ri][rj];
    add_res(ri - i, s1, n1);
    add_res(rj - j, s2, n2);
    ri = i, rj = j;
  }
  
  reverse(s1, s1 + n1);
  printf("%s%s\n", s1, s2);
  return 0;
}
           

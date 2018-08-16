/******************************************************************/
/* ACM ICPC 2012-2013                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tashkent - Tbilisi, December 2, 2012 */
/******************************************************************/
/* Problem L. Labyrinth of the Minotaur                           */
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
 * Date: 2012.11.23
 */

#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int maxS = 2000;

typedef int mas[maxS + 1][maxS + 1];

int dx[] = {1, 0, -1, 0};
int dy[] = {0, -1, 0, 1};

int h, w;
char str[maxS + 1];
mas s, u1, u2;

int cor( int x, int y, int k )
{
  x += dx[k], y += dy[k];
  return 1 <= x && x <= w && 1 <= y && y <= h && !s[y][x];
}

int add( int k, int dk )
{
  return (k + dk + 4) & 3;
}

void go( int x, int y, int k, int dk, mas &u )
{
  while (x != w || y != h)
  {
    u[y][x] = 1;
    if (cor(x, y, add(k, dk)))
      k = add(k, dk);
    else while (!cor(x, y, k))
      k = add(k, -dk);
    x += dx[k], y += dy[k];
  }
  u[y][x] = 1;
}

void calc( mas &m )
{
  for (int i = 1; i <= h; i++)
    for (int j = 1; j <= w; j++)
      m[i][j] += m[i - 1][j] + m[i][j - 1] - m[i - 1][j - 1];
}

inline int is( int x, int y, int l, mas &m )
{
  return m[y + l][x + l] - m[y][x + l] - m[y + l][x] + m[y][x];
}

inline int bs( int x, int y, int ma, mas &m1, mas &m2)
{
  int mi = 0, l;
  while (mi < ma) {
    l = (mi + ma + 1) / 2;
    if (is(x, y, l, m1) && is(x, y, l, m2))
      ma = l - 1;
    else
      mi = l;
  }
  return mi;
}

int main()
{
  #define NAME "labyrinth"
  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));

  assert(scanf("%d%d ", &w, &h) == 2);
  assert(1 <= h && h <= maxS);
  assert(1 <= w && w <= maxS);
  forn(i, h)
  {
    assert(gets(str));
    assert((int)strlen(str) == w);
    forn(j, w)
      s[i + 1][j + 1] = (str[j] == '#');
  }

  go(1, 1, 0, 1, u1);
  go(1, 1, 3, -1, u2);
  s[1][1] = s[h][w] = 1;

  calc(u1), calc(u2), calc(s);

  int res = maxS + 1, rx = 0, ry = 0, cnt = 0;
  forn(x, w)
    forn(y, h)
    {
      int ma = min(res - 1, min(w - x, h - y));
      int l = bs(x, y, ma, u1, u2) + 1;
      if (l <= ma && !is(x, y, l, s))
        res = l, rx = x, ry = y;
    }
  fprintf(stderr, "cnt = %d\n", cnt);

  if (res > maxS)
    puts("Impossible");
  else
    printf("%d %d %d\n", res, rx + 1, ry + 1);
  return 0;
}


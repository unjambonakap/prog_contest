/******************************************************************/
/* ACM ICPC 2012-2013                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tashkent - Tbilisi, December 2, 2012 */
/******************************************************************/
/* Problem F. Folding Snake Cube                                  */
/*                                                                */
/* Original idea         Roman Elizarov                           */
/* Problem statement     Roman Elizarov                           */
/* Test set              Roman Elizarov                           */
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
#include <algorithm>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int L = 15;

int bn, pos[256], rx[27], ry[27], rz[27], is[27];
char buf[27], ans[3][12], s[L][L + 1];
int u[3][3][3];

int dx[] = {1, -1, 0, 0, 0, 0};
int dy[] = {0, 0, 1, -1, 0, 0};
int dz[] = {0, 0, 0, 0, 1, -1};

void set_cell( int i, int x, int y, int z )
{
  rx[i] = x, ry[i] = y, rz[i] = z, u[x][y][z] = i;
}

void free_cell( int i )
{
  u[rx[i]][ry[i]][rz[i]] = -1;
}

void f( int i, int x, int y, int z )
{
  if (!(0 <= x && x < 3 && 0 <= y && y < 3 && 0 <= z && z < 3 && u[x][y][z] == -1))
    return;
  set_cell(i, x, y, z);
  if (i == 26)
  {
    forn(i, 3)
      forn(j, 3)
        forn(k, 3)
          ans[j][k + i * 4] = buf[u[i][j][k]];
    forn(i, 3)
      forn(j, 2)
        ans[i][3 + j * 4] = ' ';
    forn(i, 3)
      puts(ans[i]);
    exit(0);
  }
  forn(j, 6)
    if ((dx[j] * (rx[i] - rx[i - 1]) + dy[j] * (ry[i] - ry[i - 1]) + dz[j] * (rz[i] - rz[i - 1]) == 0) == (is[i - 1] == 0))
      f(i + 1, x + dx[j], y + dy[j], z + dz[j]);
  free_cell(i);
}

void go( int x0, int y0, int z0, int x1, int y1, int z1 )
{
  memset(u, -1, sizeof(u));
  set_cell(0, x0, y0, z0);
  f(1, x1, y1, z1);
}

int main()
{
  #define NAME "folding"
  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));

  bn = 0;
  forn(i, 13)
    buf[bn++] = 'A' + i, buf[bn++] = 'a' + i;
  buf[bn++] = 'A' + 13;
  assert(bn == 27);
  memset(pos, -1, sizeof(pos));
  forn(i, bn)
    pos[(int)buf[i]] = i;

  memset(rx, -1, sizeof(rx));
  forn(i, L)
  {
    assert(gets(s[i]));
    assert((int)strlen(s[i]) == L);
    forn(j, L)
      if (s[i][j] != '.')
      {
        int t = (unsigned char)s[i][j];
        assert(pos[t] != -1 && rx[pos[t]] == -1);
        rx[pos[t]] = i, ry[pos[t]] = j;
      }
  }
  forn(i, bn - 1)
    assert(abs(rx[i + 1] - rx[i]) + abs(ry[i + 1] - ry[i]) == 1);
  forn(i, bn - 2)
    is[i] = (rx[i + 1] - rx[i]) * (rx[i + 2] - rx[i + 1]) + (ry[i + 1] - ry[i]) * (ry[i + 2] - ry[i + 1]);
  
  go(0, 0, 0, 0, 0, 1);
  go(0, 0, 1, 0, 0, 0);
  go(0, 0, 1, 0, 1, 1);
  go(0, 1, 1, 0, 0, 1);
  go(0, 1, 1, 1, 1, 1);
  go(1, 1, 1, 0, 1, 1);

  assert(0); // impossible
  return 0;
}


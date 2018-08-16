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

#define KOEF 3

const int maxN = (int)3e5;
const int E = 52;
const int maxH = maxN * KOEF + E * 50;

int n, a[maxN];
ll h[maxH];
int pos = 0, hf[maxH];
ll x = 0, res = 0;
int cnt1 = 0, cnt2 = 0, cnt3 = 0;

int isP( int x )
{
  for (int i = 2; i * i <= x; i++) 
    if (x % i == 0)
      return 0;
  return 1;
}

struct HashTable
{
  int size;
  ll *h;
  int *hf;

  void init()
  {
    size *= KOEF, size += 10;
    while (!isP(size))
      size++;
    h = ::h + pos;
    hf = ::hf + pos;
    pos += size;
    assert(pos <= maxH);
  }

  inline int get_i( ll hash )
  {
    hash += 13;
    cnt1++;
    assert(size > 0);
    int i = hash % size;
    while (h[i] && h[i] != hash)
    {
      cnt3++;
      if (++i == size)
        i = 0;
    }
    return i;
  }

  int &get( ll hash )
  {
    int i = get_i(hash);
    if (!h[i])
    {
      //printf("add: %I64d to %d of %d\n", hash, i, size);
      cnt2++, h[i] = hash + 13;
    }
    return hf[i];
  }
};

int num[E + 1];
HashTable table[E + 1];

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

  int cnt = 0;
  forn(r, n)
  {
    //printf("cnt = %d\n", cnt);
    ll bit = 1LL << a[r];
    table[cnt].size++;
    cnt += (x & bit) ? -1 : 1;
    x ^= bit;
  }
  //printf("cnt = %d\nok\n", cnt);
  table[cnt].size++;

  forn(i, E + 1)
  {
    num[i] = table[i].size, table[i].init();
    //printf("size[%d] = %d\n", i, table[i].size);
  }

  x = 0, cnt = 0;
  forn(r, n)
  {
    //printf("cnt = %d\n", cnt);
    res += table[cnt].get(x)++;

    ll bit = 1LL << a[r];
    cnt += (x & bit) ? -1 : 1;
    x ^= bit;
  }
  //printf("cnt = %d\n", cnt);
  res += table[cnt].get(x)++;

  //printf("res = %I64d\n", res);

  forn(i, E)
  {
    if (!num[i + 1])
      continue;

    HashTable &t = table[i], &T = table[i + 1];
    ll x;
    //printf("size[%d] = %d --> %d\n", i, t.size, T.size);
    //forn(j, t.size)
    //  printf("%I64d\n", t.h[j]);
    forn(j, t.size)
      if ((x = t.h[j]) != 0)
      {
        x -= 13;
        //printf("%d : %I64d\n", i, x);
        forn(bit, E)
        {
          ll b = 1LL << bit;
          if (!(x & b))
          {
            //if (b <= 8)
            //  printf("%I64d + %I64d\n", t.h[i], b);
            res += (ll)t.hf[j] * T.hf[T.get_i(x ^ b)];
          }
        }
      }
  }

  fprintf(stderr, "call get: %d\n", cnt1);
  fprintf(stderr, "overhead: %d\n", cnt3);
  fprintf(stderr, "size:     %d\n", cnt2);

  cout << res << endl;
  return 0;
}


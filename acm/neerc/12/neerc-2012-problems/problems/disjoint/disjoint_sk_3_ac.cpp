/******************************************************************/
/* ACM ICPC 2012-2013                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tashkent - Tbilisi, December 2, 2012 */
/******************************************************************/
/* Problem D. Disjoint Regular Expressions                        */
/*                                                                */
/* Original idea         Roman Elizarov                           */
/* Problem statement     Andrey Stankevich                        */
/* Test set              Andrey Stankevich                        */
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
#include <cctype>

#include <algorithm>
#include <vector>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define pb push_back

typedef vector <int> vi;

const int maxN = 100; // string's length
const int maxT = maxN * 4; // number of nodes
const int maxS = maxN * 4; // number of states in automaton
const int maxQ = maxS * maxS * 2; // length of queue

const char *typeName[] = {"", "*", "|", "+"};

struct node
{
  enum {A, STAR, OR, CONCAT};

  int type, l, r;
};

int vn = 0;
node t[maxT];

int newNode( int type, int l, int r )
{
  assert(vn < maxT);
  t[vn].type = type;
  t[vn].l = l;
  t[vn].r = r;
  return vn++;
}

int pos;
char s[maxN + 1];

void Skip( char c )
{
  assert(s[pos++] == c);
}

int Expr();

int Item()
{
  int res;
  if (s[pos] == '(')
  {
    Skip('(');
    res = Expr();
    Skip(')');
  }
  else
  {
    assert(isalpha(s[pos]));
    res = newNode(node::A, s[pos++], -1);
  }
  while (s[pos] == '*')
  {
    Skip('*');
    res = newNode(node::STAR, res, -1);
  }
  return res;
}

int ConCat()
{
  int v = Item();
  while (s[pos] && s[pos] != ')' && s[pos] != '|')
    v = newNode(node::CONCAT, v, Item());
  return v;
}

int Expr()
{
  int v = ConCat();
  while (s[pos] == '|')
  {
    Skip('|');
    v = newNode(node::OR, v, ConCat());
  }
  return v;
}

struct Automaton
{
  int n;
  vi next[maxS];
  vi ch[maxS];

  void add( int i, int j, char c )
  {
    next[i].pb(j);
    ch[i].pb(c);
  }
};

void go( int v, Automaton &a )
{
  int st = a.n++; // start
  if (t[v].type == node::A)
    a.add(st, a.n, t[v].l);
  else if (t[v].type == node::STAR)
  {
    go(t[v].l, a);
    a.add(st, st + 1, -1);
    a.add(st, a.n, -1);
    a.add(a.n - 1, st, -1);
  }
  else if (t[v].type == node::OR)
  {
    go(t[v].l, a);
    int m = a.n;
    go(t[v].r, a);
    a.add(st, st + 1, -1);
    a.add(st, m, -1);
    a.add(m - 1, a.n, -1);
    a.add(a.n - 1, a.n, -1);
  }
  else if (t[v].type == node::CONCAT)
  {
    a.add(st, st + 1, -1);
    go(t[v].l, a);
    a.add(a.n - 1, a.n, -1);
    go(t[v].r, a);
    a.add(a.n - 1, a.n, -1);
  }
  a.n++; // end
}

void Read( Automaton &a )
{
  assert(gets(s));
  int sn = strlen(s);
  assert(1 <= sn && sn <= maxN);
  pos = 0;
  int root = Expr();
  go(root, a);
}

#define S [maxS][maxS][2]

Automaton a[2];
int qst = maxQ, qen = maxQ;
int qx[maxQ * 2], qy[maxQ * 2], qz[maxQ * 2];
int d S, px S, py S, pz S, pc S;
int rn, r[maxQ];

#define I [x][y][z]

void AddQ( int x, int y, int D, int PX, int PY, int PZ, int PC )
{
  int add = (PC != -1), z = PZ || add;
  D += add;
  if (d I > D)
  {
    d I = D;
    px I = PX, py I = PY, pz I = PZ, pc I = PC;
    if (add)
      qx[qen] = x, qy[qen] = y, qz[qen++] = z;
    else
      qx[--qst] = x, qy[qst] = y, qz[qst] = z;
  }
}

int main()
{
  #define NAME "disjoint"
  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));

  forn(t, 2)
    Read(a[t]);
  memset(d, 0x70, sizeof(d));
  AddQ(0, 0, 0, 0, 0, 0, -1);
  while (qst < qen)
  {
    int x = qx[qst], y = qy[qst], z = qz[qst++], D = d I;
    forn(i, a[0].next[x].size())
      forn(j, a[1].next[y].size())
        if (a[0].ch[x][i] == a[1].ch[y][j])
          AddQ(a[0].next[x][i], a[1].next[y][j], D, x, y, z, a[0].ch[x][i]);
    forn(i, a[0].next[x].size())
      if (a[0].ch[x][i] == -1)
        AddQ(a[0].next[x][i], y, D, x, y, z, -1);
    forn(j, a[1].next[y].size())
      if (a[1].ch[y][j] == -1)
        AddQ(x, a[1].next[y][j], D, x, y, z, -1);
  }

  int x = a[0].n - 1, y = a[1].n - 1, z = 1;
  if (d I > maxQ)
    puts("Correct");
  else
  {
    puts("Wrong");
    while (x || y)
    {
      int x1 = px I, y1 = py I, z1 = pz I, c = pc I;
      if (c != -1)
        r[rn++] = c;
      x = x1, y = y1, z = z1;
    }
    while (rn--)
      putchar(r[rn]);
    puts("");
  }
  return 0;
}


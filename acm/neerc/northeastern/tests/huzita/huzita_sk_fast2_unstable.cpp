/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

/* Template */

#include <cstdarg>
#include <ctime>
#include <cmath>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>

#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <functional>
#include <map>
#include <set>
#include <fstream>
#include <queue>

using namespace std;

#ifdef _WIN32
#  define I64 "%I64d"
#else
#  define I64 "%Ld"
#endif

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define fornd(i, n) for (int i = (int)(n) - 1; i >= 0; i--)
#define forab(i, a, b) for (int i = (int)(a); i <= (int)(b); i++)
#define forabd(i, a, b) for (int i = (int)(b); i >= (int)(a); i--)
#define forit(i, a) for (__typeof((a).begin()) i = (a).begin(); i != (a).end(); i++)
#define sz(a) (int)(a).size()
#define all(a) (a).begin(), (a).end()
#define zero(a) memset(a, 0, sizeof(a))
#define fill(a, x) memset(a, x, sizeof(a))
#define pb push_back
#define mp make_pair

#define EOL(i, n) " \n"[i == (n) - 1]
#define LEN(a) (int)(sizeof(a) / sizeof(a[0]))
#define IS(a, i) (((a) >> (i)) & 1)
#define LAST(a) a[sz(a) - 1]

typedef unsigned int uint;
typedef double dbl;
typedef long long ll;
typedef unsigned long long ull;
typedef vector <int> vi;
typedef pair <int, int> pii;
typedef unsigned char byte;

template <class T> T inline sqr(T x) { return x * x; }
template <class T> inline void relaxMin( T &a, T b ) { a = min(a, b); }
template <class T> inline void relaxMax( T &a, T b ) { a = max(a, b); }

string str( int i ) { char s[100]; sprintf(s, "%d", i); return string(s); }

template <class T> inline T sign( T x ) { return x > 0 ? 1 : (x < 0 ? -1 : 0); }
template <class T> inline T myAbs( T a ) { return a > 0 ? a : -a; }

#define DEBUG 1
void err( const char *fmt, ... )
{
  #if DEBUG
  va_list list;
  va_start(list, fmt);
  vfprintf(stderr, fmt, list);
  fflush(stderr);
  #endif
}

const dbl eps = 1e-12;

struct pnt
{
  dbl x, y;

  pnt( dbl _x = 0, dbl _y = 0 ) : x(_x), y(_y) { }

  inline pnt operator + ( const pnt &p ) const { return pnt(x + p.x, y + p.y); }
  inline pnt operator - ( const pnt &p ) const { return pnt(x - p.x, y - p.y); }
  inline pnt operator * ( const dbl &k ) const { return pnt(x * k, y * k); }
  inline pnt operator / ( const dbl &k ) const { return pnt(x / k, y / k); }

  inline dbl operator * ( const pnt &p ) const { return x * p.y - y * p.x; }
  inline dbl operator ^ ( const pnt &p ) const { return x * p.x + y * p.y; }

  inline bool operator == ( const pnt &p ) const { return fabs(x - p.x) + fabs(y - p.y) < eps; }
  inline bool operator != ( const pnt &p ) const { return fabs(x - p.x) + fabs(y - p.y) > eps; }

  inline void read() { assert(scanf("%lf%lf", &x, &y) == 2); }

  inline dbl d2() const { return x * x + y * y; }
  inline dbl d() const { return sqrt(d2()); }

  inline pnt norm() const { return *this / d(); }
  inline pnt ort() const { return pnt(-y, x); }
  inline dbl ang() const { return atan2(y, x); }

  pnt rot( dbl a )
  {
    dbl co = cos(a), si = sin(a);
    return pnt(x * co - y * si, x * si + y * co);
  }

  static const int prec = 20;
  void out() { printf("%.*lf %.*lf ", prec, (double)x, prec, (double)y); }
  void out2() { out(), puts(""); }
  string toString()
  {
    static char buf[99];
    sprintf(buf, "(%.*lf,%.*lf)", prec, (double)x, prec, (double)y);
    return string(buf);
  }
};

inline pnt pntByAng( dbl a ) { return pnt(cos(a), sin(a)); }

#define NAME "huzita"

/* The main part */

pnt p[2], l1[2], l2[2], no[2];
dbl B[2];

inline dbl getT( int i, const pnt &v )
{
  dbl B = (p[i] - l1[i]) ^ no[i], A = v ^ no[i];
  dbl t = -B / A; // (p[i] + t * v) ^ no[i] = l1[i] ^ no[i]
  pnt tmp = p[i] + v * (t / 2);
  return tmp ^ v;
}

void Out( int i, pnt normal )
{       
  dbl t = getT(i, normal);
  (normal * t).out();
  (normal * t + normal.ort()).out();
  puts("");
}

int cnt = 0;

const int M = (int)1e5;

dbl MAX1, MAX2, D1, D2, STEP1, STEP2;
dbl co1[M + 1], si1[M + 1];
dbl co2[M + 1], si2[M + 1];

inline dbl F( dbl ang ) // c1 - c2
{
  cnt++;

  dbl x = 0, y = 0;
  int sx = 1, sy = 1, sf = 0;
  if (ang > M_PI)
    ang -= M_PI, sx *= -1, sy *= -1;
  if (ang > M_PI / 2)
    ang = M_PI - ang, sx *= -1;
  if (ang > M_PI / 4)
    ang = M_PI / 2 - ang, sf = 1;

  // ang <= M_PI / 4
  int i = (int)(ang * STEP1);
  int j = (int)((ang - i * D1) * STEP2);
  x = co1[i] * co2[j] - si1[i] * si2[j]; // cos(i + j)
  y = co1[i] * si2[j] + si1[i] * co2[j]; // sin(i + j)

  if (sf)
    swap(x, y);
  x *= sx, y *= sy;

  pnt v(x, y); // normal
  return ((p[0] - p[1]) ^ v) - (B[0] / (v ^ no[0]) - B[1] / (v ^ no[1])) / 2;
}

void Cor( dbl &a ) 
{
  while (a < -eps)
    a += M_PI;
  while (a > M_PI - eps)
    a -= M_PI;
}

bool Find( dbl la, dbl ra )
{
  #define GOOD(a) { Out(0, pntByAng(a)); return 1; }
  #define G(a) fabs(F(a))
  #define MIN 1e-7

  if (la > ra)
    return 0;

  const int K = 10;
  dbl f[K + 1], ang[K + 1];
  forn(i, K + 1)
  {
    f[i] = F(ang[i] = la + (ra - la) * i / K);
    if (fabs(f[i]) < eps) // CASE #1, we are lucky
      GOOD(ang[i])
  }
  forn(i, K)
    if ((f[i] > eps) != (f[i + 1] > eps))
    {
      la = ang[i], ra = ang[i + 1];
      if (f[i] > eps)
        swap(la, ra);
      while (fabs(la - ra) > eps) // CASE #2, 2-Search
      {
        dbl ma = (la + ra) / 2;
        if (F(ma) < 0)
          la = ma;
        else
          ra = ma;
      }
      GOOD((la + ra) / 2)
    }

  int mi = 1;
  forab(i, 1, K - 1)
    if (fabs(f[i]) < fabs(f[mi]))
      mi = i;
  la = ang[mi - 1], ra = ang[mi + 1];
  dbl ma = (la + ra) / 2;
  dbl fm = G(ma);
  while (fabs(ra - la) > eps) // CASE #3, 3-Search
  {
    dbl a = (la + ma) / 2, fa = G(a);
    dbl b = (ra + ma) / 2, fb = G(b);
    if (fa < fm)
      ra = ma, fm = fa, ma = a;
    else if (fb < fm)
      la = ma, fm = fb, ma = b;
    else
      la = a, ra = b;
  }
  if (fm < MIN)
    GOOD(ma)
  return 0;
}

void Solve()
{
  forn(i, 2)
  {
    l1[i].read(), l2[i].read(), p[i].read();
    no[i] = (l2[i] - l1[i]).norm().ort();
    B[i] = (p[i] - l1[i]) ^ no[i];
  }

  dbl a = no[0].ort().ang();
  dbl b = no[1].ort().ang();
  Cor(a), Cor(b);
  if (a > b)
    swap(a, b);
 
  dbl epsAng = 1e-6;
  if (!(Find(a + epsAng, b - epsAng) || Find(b + epsAng, a + M_PI - epsAng)))
    puts("0 0 0 0");
}

int main()
{
  MAX1 = M_PI / 4;
  MAX2 = D1 = MAX1 / M;
  D2 = MAX2 / M;
  forn(i, M + 1)
  {
    dbl ang = D1 * i;
    co1[i] = cos(ang), si1[i] = sin(ang);
    ang = D2 * i;
    co2[i] = cos(ang), si2[i] = sin(ang);
  }
  STEP1 = 1.0 / D1, STEP2 = 1.0 / D2;

  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));

  int tn;
  assert(scanf("%d", &tn) == 1);
  forn(tt, tn)
    Solve();

  err(" tn = %d\n", tn);
  err("cnt = %d\n", cnt);
  return 0;
}

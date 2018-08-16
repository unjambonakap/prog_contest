// O(m^3 log n + m n) solution to 'Periodic points'.
// David Garcia Soriano.
#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;

int mod;

typedef long long ll;
typedef vector<ll> row;
typedef vector<row> matrix;

matrix multiply(int m, const matrix &a, const matrix &b) {
  matrix c(m, row(m));
  for (int i = 0; i < m; ++i)
    for (int j = 0; j < m; ++j)
      for (int k = 0; k < m; ++k)
        c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % mod;
  return c;
}

int sign(int a) { return (a == 0) ? 0 : (a > 0 ? 1 : -1); }

void next(int& left, int& right, int l, int r) {
  if (left < 0) left = l; else if (left > 0) left = r;
  if (right > 0) right = r; else if (right < 0) right = l;
}

int main() {
  int m, n;
  while (scanf("%i", &m), m) {
    vector<ll> a(m + 1);
    matrix mat(m, row(m));
    for (int i = 0; i <= m; ++i)
      scanf("%lli", &a[i]);
    scanf("%i", &n);
    scanf("%i", &mod);

    for (int i = 0; i < m; ++i)
      for (int j = min(a[i], a[i + 1]); j < max(a[i], a[i + 1]); ++j)
        mat[j][i] = 1;

    matrix ret(m, row(m));
    for (int i = 0; i < m; ++i) ret[i][i] = 1;

    for (int t = 1; t <= n; t *= 2) {
      if (n & t) ret = multiply(m, ret, mat);
      mat = multiply(m, mat, mat);
    }

    int total = 0;
    for (int i = 0; i < m; ++i)
      total = (total + ret[i][i]) % mod;

    int s[m + 1][2];
    for (int i = 0; i <= m; ++i) {
      s[i][0] = i > 0 ? sign(a[i - 1] - a[i]) : 0; // moving left
      s[i][1] = i < m ? sign(a[i + 1] - a[i]) : 0; // moving right
    }

    bool inf = false;
    for (int i = 0; i <= m && !inf; ++i) {
      int x = i, sx[2] = { -1, 1 };
      bool can_inf = true;
      for (int j = 0; j < n; ++j) {
        if (sx[1] > 0)      can_inf &= x < m && (abs(a[x + 1] - a[x]) == 1);
        else if (sx[1] < 0) can_inf &= x > 0 && (abs(a[x - 1] - a[x]) == 1);
        else can_inf = false;

        next(sx[0], sx[1], s[x][0], s[x][1]);
        x = a[x];
      }

      if (x == i) {
        ++total;
        if (sx[0] < 0) --total;   // left decreasing, already included in [i - 1, i]
        if (sx[1] > 0) --total;   // right increasing, already included in [i, i + 1]
        if (i < m && sx[1] > 0 && can_inf) inf = true;
        if (total < 0) total += mod;
      }
    }
    if (inf) puts("Infinity");
    else printf("%i\n", total % mod);
  }

  return 0;
}

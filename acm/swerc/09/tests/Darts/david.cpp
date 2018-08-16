// Approximate DP solution to darts, repeating iterations to update values for n <= 20.
// David Garcia Soriano.
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

const int sections = 20;
const int board[sections + 2] = { 5, 20, 1, 18, 4, 13, 6, 10, 15, 2, 17, 3, 19, 7, 16, 8, 11, 14, 9, 12, 5, 20 };

const int maxn = 501;

double f[maxn + 1][maxn + 1][2];  // prob that player i wins if he starts

int next(int a, int b) { return a >= b ? a - b : a; }

int main() {
  for (int n = 0; n <= maxn; ++n) f[0][n][0] = f[n][0][1] = 1;
  for (int n = 1; n <= maxn; ++n)
    for (int m = 1; m <= maxn; ++m) {
      // lower bounds on f
      if (n <= sections) f[n][m][0] = (double)min(n, sections) / 20;
      if (m <= sections) f[n][m][1] = (double)min(m, 20) / 3;

      for (int tries = 0; tries < 100; ++tries) {
        double a = 0;
        for (int i = 1; i <= sections; ++i)
          a += f[next(n, board[i])][m][1];
        f[n][m][0] = 1 - a / sections;

        double b = 1e300;
        for (int i = 1; i <= sections; ++i) {
          double val = 0;
          for (int j = -1; j <= 1; ++j) 
            val += f[n][next(m, board[i + j])][0];
          val /= 3;
          if (val < b)
            b = val;
        }
        f[n][m][1] = 1 - b;

        if (n > sections) break;
      }
    }

  int n;
  while (scanf("%i", &n) == 1 && n != 0)
    printf("%.12lf %.12lf\n", f[n][n][0], f[n][n][1]);
  return 0;
}

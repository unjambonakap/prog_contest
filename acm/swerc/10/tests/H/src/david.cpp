// O(length^3 * letters^2) DP solution to 'Assembly line'.
// David Garcia Soriano.
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int infinity = 1000000000;

const int maxl = 'z' - 'a' + 1, maxn = 200;
int mult[maxl][maxl], mult_cost[maxl][maxl];

char letter[maxl], str[maxn + 1];
int letter_pos[256];

int best[maxn][maxn + 1][maxl];

int main() {
  int k;
  bool first = true;
  while (scanf("%i", &k), k) {
    if (!first) puts(""); first = false;

    for (int i = 0; i < k; ++i) {
      scanf(" %c", &letter[i]);
      letter_pos[letter[i]] = i;
    }

    for (int i = 0; i < k; ++i)
      for (int j = 0; j < k; ++j) {
        char l;
        scanf(" %i-%c", &mult_cost[i][j], &l);
        mult[i][j] = letter_pos[l];
      }

    int lines;
    scanf("%i", &lines);
    while (lines--) {
      scanf("%s", str);
      int n = strlen(str);
      for (int i = 0; i < n; ++i) 
        str[i] = letter_pos[str[i]];

      fill(&best[0][0][0], &best[n][0][0], infinity);
      for (int i = n - 1; i >= 0; --i) {
        best[i][i + 1][str[i]] = 0;
        for (int j = i + 2; j <= n; ++j)
          for (int m = i + 1; m < j; ++m)
            for (int l1 = 0; l1 < k; ++l1)
              for (int l2 = 0; l2 < k; ++l2) {
                int prod = mult[l1][l2],
                    cost = best[i][m][l1] + best[m][j][l2] + mult_cost[l1][l2];
                if (cost < best[i][j][prod]) best[i][j][prod] = cost;
              }
      }

      int l = min_element(&best[0][n][0], &best[0][n][k]) - &best[0][n][0];
      printf("%i-%c\n", best[0][n][l], letter[l]);
    }
  }
  return 0;
}

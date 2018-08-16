#include "testlib.h"

int main( int argc, char **argv ) {
  registerTestlibCmd(argc, argv);
  setName("checker for problem G (Galaxy Interconnections) from ACM ICPC 2011 NEERC Nothern Quaterfinals");

  int n = inf.readInt();
  int k = inf.readInt();
  int m = inf.readInt();

  int *color = new int[n]; // Хрен его знает, как этот чекер под виндой компилировать будут, лучше не буду память на стеке выделять.
  for (int i = 0; i < n; i++) {
    color[i] = ouf.readInt();
    if (color[i] < 1 || color[i] > k)
      quitf(_pe, "planet #%d has bad scientific direction: %d", i + 1, color[i]);
    color[i]--;
  }
  ouf.seekEof();
  ouf.readEof();

  std::vector <int> *v = new std::vector<int>[n];
  for (int i = 0; i < m; i++) {
    int a = inf.readInt() - 1;
    int b = inf.readInt() - 1;
    if (color[a] == color[b])
      quitf(_wa, "planets #%d and #%d are connected and have same scientific directions: %d", a + 1, b + 1, color[a]);
    v[a].push_back(b);
    v[b].push_back(a);
  }

  int **d = new int*[1 << k];
  // Можно соптимизировать по памяти в 32 раза, угадайте, как?
  for (int i = 0; i < (1 << k); i++) {
    d[i] = new int[n];
    memset(d[i], 0, sizeof(d[i][0]) * n);
  }
  for (int i = 0; i < n; i++)
    d[1 << color[i]][i] = 1;
  for (int cnt = 1; cnt < k; cnt++) {
    for (int pr = 0; pr < (1 << k); pr++) {
      int sum = 0;
      for (int i = 0; i < k; i++)
        sum += (pr >> i) & 1;
      if (sum != cnt)
        continue;
      for (int i = 0; i < n; i++) {
        if (!d[pr][i])
          continue;
        for (int j = 0; j < (int)v[i].size(); j++) {
          if (pr & (1 << color[v[i][j]]))
            continue;
          d[pr | (1 << color[v[i][j]])][v[i][j]] = 1;
        }
      }
    }
  }
  for (int i = 0; i < n; i++)
    if (!d[(1 << k) - 1][i])
      quitf(_wa, "cannot launch research audit from planet #%d", i + 1);

  quitf(_ok, "n=%d,m=%d,k=%d", n, m, k);
}


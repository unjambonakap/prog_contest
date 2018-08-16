// O(n^4) solution to 'Fake scoreboard' using max-flow with 'smart' updates.
//
// After the initial max-flow computation, it determines which edges can be removed at no cost. This
// is accomplished by updating the max-flow network to that of a slightly modified graph, with the
// guarantee that the new flow can be at most 1 unit larger than the previous one, so each such step
// only needs O(E) = O(n^2) time.
// Since this is repeated O(n^2) times, the total running time is O(n^4).
//
// David Garcia Soriano.
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <numeric>
#include <vector>
using namespace std;

const int maxn = 192;
int cap[maxn][maxn], deg[maxn], edge[maxn][maxn], queue[maxn], prev[maxn];

// Leaves residual capacities in cap[] and returs the max flow value.
int maxflow(int n, int src, int sink) {
  int flow = 0, i, v, w;
  for (;;) {
    // Find a shortest augmenting path with BFS
    fill(&prev[0], &prev[n], -1);
    int startq = 0, endq = 0;
    prev[queue[endq++] = src] = -2;
    while (startq != endq && prev[sink] < 0)
      for (v = queue[startq++], i = deg[v] - 1; i >= 0; --i)
        if (prev[w = edge[v][i]] < 0 && cap[v][w] > 0)
          prev[queue[endq++] = w] = v;
    if (prev[sink] == -1) break;

    // For each reachable vertex adjacent to the sink, find the path from the source,
    // remove these edges, and repeat while possible.
    for (i = 0; i < n; i++) if (cap[i][sink] && prev[i] != -1) {
      int minc = cap[i][sink];
      for (v = i; v != src; v = prev[v]) minc = min(minc, cap[prev[v]][v]);
      if (!minc) continue;

      cap[i][sink] -= minc;
      cap[sink][i] += minc;
      for (v = i; v != src; v = prev[v]) {
        cap[prev[v]][v] -= minc;
        cap[v][prev[v]] += minc;
      }
      flow += minc;
    }
  }
  return flow;
}

// Add an edge between 'a' and 'b' with capacity 'c'
void add(int a, int b, int c) {
  edge[a][deg[a]++] = b;
  edge[b][deg[b]++] = a;
  cap[a][b] = c; cap[b][a] = 0;
}

int main() {
  int ly, lx;
  bool first = true;
  while (scanf("%i%i", &ly, &lx), ly) {
    vector<int> sumx(lx), sumy(ly);
    for (int i = 0; i < ly; ++i) scanf("%i", &sumy[i]);
    for (int j = 0; j < lx; ++j) scanf("%i", &sumx[j]);
    if (!first) puts(""); else first = false;

    int n = ly + lx + 2, src = n - 1, sink = n - 2,
        total = accumulate(sumx.begin(), sumx.end(), 0);
    fill(&deg[0], &deg[n], 0);
    for (int i = 0; i < n; ++i)
      cap[i][sink] = 0;
    for (int y = 0; y < ly; ++y)
      add(src, y, sumy[y]);
    for (int x = 0; x < lx; ++x)
      add(ly + x, sink, sumx[x]);
    for (int i = 0; i < ly * lx; ++i)
      add(i / lx, ly + (i % lx), 1);

    if (accumulate(sumy.begin(), sumy.end(), 0) != total || maxflow(n, src, sink) != total) puts("Impossible");
    else
      for (int i = 0; i < ly * lx; ++i) {
        int y = i / lx, x = i % lx;
        bool canbezero = (cap[y][ly + x] != 0);
        if (!canbezero) {
          // Try not using this edge
          ++cap[src][y];
          ++cap[ly + x][sink];
          cap[y][ly + x] = cap[ly + x][y] = 0;
          if (maxflow(n, src, sink) > 0) {
            canbezero = true;
          } else {
            --cap[src][y];
            --cap[ly + x][sink];
          }
        }
        cap[y][ly + x] = cap[ly + x][y] = 0;

        if (canbezero) putchar('N');
        else { --total; putchar('Y'); }
        if (i % lx == lx - 1) puts("");
      }
  }
  return 0;
}

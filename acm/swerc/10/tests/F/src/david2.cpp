// O(n^2 2^n) solution to 'Jumping monkey', simplest version.
// David Garcia Soriano.
#include <algorithm>
#include <cstdio>
#include <deque>
#include <vector>
using namespace std;

const int maxn = 21;
int dist[1 << maxn], shoot[1 << maxn], prev[1 << maxn];

int main() {
  int n, m;
  while (scanf("%i%i\n", &n, &m), n) {
    int edge[n];
    fill(&edge[0], &edge[n], 0);
    for (int i = 0; i < m; ++i) {
      int a, b;
      scanf("%i%i", &a, &b);
      edge[a] |= 1 << b;
      edge[b] |= 1 << a;
    }

    deque<int> q;

    fill(&dist[0], &dist[1 << n], -1);
    q.push_back((1 << n) - 1);
    dist[(1 << n) - 1] = 0;

    while (dist[0] < 0 && !q.empty()) {
      int s = q.front(), d = dist[s]; q.pop_front();
      for (int i = 0; i < n; ++i) if (s & (1 << i)) {
        int t = 0;
        for (int j = 0; j < n; ++j) if ((i != j) && (s & (1 << j)))
          t |= edge[j];
        if (dist[t] < 0) {
          dist[t] = d + 1;
          shoot[t] = i;
          prev[t] = s;
          q.push_back(t);
        }
      }
    }

    if (dist[0] < 0) puts("Impossible");
    else {
      printf("%i:", dist[0]);
      vector<int> path;
      int s = 0;
      while (s != ((1 << n) - 1)) {
        path.push_back(shoot[s]);
        s = prev[s];
      }
      for (int i = path.size() - 1; i >= 0; --i)
        printf(" %i", path[i]);
      puts("");
    }
  }

  return 0;
}

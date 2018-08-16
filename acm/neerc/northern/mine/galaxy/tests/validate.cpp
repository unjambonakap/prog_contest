#include "testlib.h"
#include <set>

const int maxn = 5000;
const int maxk = 10;
const int maxm = 10000;

void dfs( int u, std::vector <int> *v, int *c ) {
  c[u] = 1;
  for (int i = 0; i < (int)v[u].size(); i++)
    if (!c[v[u][i]])
      dfs(v[u][i], v, c);
}

int main() {
  using namespace std;
  registerValidation();

  int n = inf.readInt(3, maxn);
  inf.readSpace();
  int k = inf.readInt(3, min(maxk, n));
  inf.readSpace();
  int m = inf.readInt(1, maxm);
  inf.readEoln();
  set <pair <int, int> > edges;
  vector <int> v[n];
  for (int i = 0; i < m; i++) {
    int a = inf.readInt(1, n) - 1;
    inf.readSpace();
    int b = inf.readInt(1, n) - 1;
    inf.readEoln();
    ensuref(a != b, "egde #%d is a loop around vertex #%d", i + 1, a + 1);
    ensuref(edges.count(make_pair(min(a, b), max(a, b))) == 0, "edge %d--%d is duplicated", a + 1, b + 1);
    edges.insert(make_pair(min(a, b), max(a, b)));
    v[a].push_back(b);
    v[b].push_back(a);
  }
  inf.readEof();

  for (int i = 0; i < n; i++)
    ensuref(int(v[i].size()) < k, "too large degree of vertex #%d", i + 1);
  for (int i = 0; i < k; i++)
    ensuref(edges.count(make_pair(min(i, (i + 1) % k), max(i, (i + 1) % k))), "no initial cycle found (%d)", i + 1);
  int c[n];
  memset(c, 0, sizeof(c[0]) * n);
  dfs(0, v, c);
  for (int i = 0; i < n; i++)
    ensuref(c[i], "vertex #%d disconnected from others", i);

  return 0;
}


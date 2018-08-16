// O(n * keys) solution to 'locks and keys'. 
// Finds a legal path, not necessarily the shortest one.
// David Garcia Soriano
#include <algorithm>
#include <cstdio>
#include <list>
#include <vector>
using namespace std;

const int maxn = 1500;

struct Edge {
  int a, b, lock;
  Edge(int aa = -1, int bb = -1, int l = -1) : a(aa), b(bb), lock(l) {}
  void reverse() { swap(a, b); }
};

vector<Edge> edge[maxn];      // destination 
int poskey[maxn];             // position of key i

int dfsin[maxn], dfsout[maxn], depth[maxn], time;
Edge prev[maxn];

void dfs(int v, int d = 0) {
  depth[v] = d;
  dfsin[v] = time++;
  for (int i = 0; i < edge[v].size(); ++i) {
    int w = edge[v][i].b;
    if (depth[w] < 0) {
      prev[w] = edge[v][i];
      dfs(w, d + 1);
    }
  }
  dfsout[v] = time;
}

int lca(int a, int b) {
  if (depth[a] > depth[b]) swap(a, b);
  while (!(dfsin[a] <= dfsin[b] && dfsout[a] >= dfsout[b]))
    a = prev[a].a;
  return a;
}

void path_to_ancestor(int a, int l, list<Edge>& ret) {
  while (a != l) {
    Edge e = prev[a]; e.reverse();
    ret.push_back(e);
    a = e.b;
  }
}

void turn_around(list<Edge>& path) {
  path.reverse();
  for (list<Edge>::iterator it = path.begin(); it != path.end(); ++it) it->reverse();
}

void path(int a, int b, list<Edge>& ret) {
  if (a != b) {
    list<Edge> ret2;
    int l = lca(a, b);
    path_to_ancestor(a, l, ret2);
    path_to_ancestor(b, l, ret);
    turn_around(ret);
    ret.splice(ret.begin(), ret2);
  }
}

bool needed[maxn], found[maxn], possible;

void full_path(int a, int b, list<Edge>& ret) {
  if (!possible) return;

  path(a, b, ret);
  list<Edge>::iterator prev = ret.begin();
  for (list<Edge>::iterator e = ret.begin(); e != ret.end();)
    if (e->lock >= 0 && !found[e->lock]) {
      int m = e->a, p = poskey[e->lock];

      // Replace path prev->->m->b with a->p->m->b
      if (needed[e->lock]) { possible = false; return; }
      needed[e->lock] = true;
      list<Edge> first, second;
      full_path(prev->a, p, first);
      full_path(p, m, second);
      found[e->lock] = true;

      second.splice(second.begin(), first);
      ret.erase(prev, e);
      ret.splice(e, second);
      prev = ++e;
    } else ++e;
}

void print(const list<Edge>& path) {
  printf("%i: ", (int)path.size());
  for (list<Edge>::const_iterator it = path.begin(); it != path.end(); ++it) {
    if (it == path.begin()) printf("%i", it->a);
    printf(" %i", it->b);
  }
  puts("");
}

int main() {
  int n, numlocks, src, dest;
  while (scanf("%i %i %i %i", &n, &numlocks, &src, &dest), n) {
    for (int i = 0; i < numlocks; ++i) scanf("%i", &poskey[i]);

    for (int i = 0; i < n; ++i) edge[i].clear();
    for (int i = 0; i < n - 1; ++i) {
      int a, b, l;
      scanf("%i%i%i", &a, &b, &l);    // l=-1 means that no lock is required
      edge[a].push_back(Edge(a, b, l));
      edge[b].push_back(Edge(b, a, l));
    }

    time = 0;
    fill(&depth[0], &depth[n], -1);
    dfs(src);

    fill(&needed[0], &needed[n], false);
    fill(&found[0], &found[n], false);
    possible = true;
    list<Edge> ret;
    full_path(src, dest, ret);
      
    if (!possible) puts("Impossible");
    else {
      if (ret.empty()) printf("0: %i\n", src);
      else print(ret);
    }
  }
  return 0;
}

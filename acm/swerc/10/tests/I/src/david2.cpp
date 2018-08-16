// O(n * keys) solution to 'locks and keys'. 
// Finds a legal path, not necessarily the shortest one.
// Similar to david.cpp, but simpler in that a DFS is performed from scratch each time we need
// to find a path in the tree.
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

int n;
vector<Edge> edge[maxn];      // destination 
int poskey[maxn];             // position of key i

bool visited[maxn];
Edge prev[maxn];

void dfs(int src, int dest) {
  visited[src] = true;
  if (src != dest)
    for (int i = 0; i < edge[src].size(); ++i) {
      int w = edge[src][i].b;
      if (!visited[w]) {
        prev[w] = edge[src][i];
        dfs(w, dest);
      }
    }
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
  fill(&visited[0], &visited[n], false);
  dfs(a, b);
  path_to_ancestor(b, a, ret);
  turn_around(ret);
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
  int numlocks, src, dest;
  while (scanf("%i %i %i %i", &n, &numlocks, &src, &dest), n) {
    for (int i = 0; i < numlocks; ++i) scanf("%i", &poskey[i]);

    for (int i = 0; i < n; ++i) edge[i].clear();
    for (int i = 0; i < n - 1; ++i) {
      int a, b, l;
      scanf("%i%i%i", &a, &b, &l);    // l=-1 means that no lock is required
      edge[a].push_back(Edge(a, b, l));
      edge[b].push_back(Edge(b, a, l));
    }

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

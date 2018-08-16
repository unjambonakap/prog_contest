// O(n * sets) solution to 'Palindromic DNA'.
// David Garcia Soriano.
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int maxn = 10000, maxv = 4 * maxn;
char str[maxn + 1];

int n, numv;
vector<int> edge[maxv];

void set(int i, int val) {
  int must = (2 * i) | val;
  edge[must ^ 1].push_back(must);
}

void add_or(int i, int v1, int j, int v2) {
  edge[(2 * i) | (v1 ^ 1)].push_back((2 * j) | v2);
  edge[(2 * j) | (v2 ^ 1)].push_back((2 * i) | v1);
}

void add_equal(int i, int j) {
  add_or(i, 1, j, 0);
  add_or(i, 0, j, 1);
}

void add_distinct(int i, int j) {
  add_or(i, 0, j, 0);
  add_or(i, 1, j, 1);
}

// Tarjan's algorithm for strongly connected components.
int dfstime, dfsin[maxv], lowlink[maxv], ncomp, comp[maxv], stack[maxv], ss;

void scc(int v) {
  int w;
  dfsin[v] = dfstime;
  lowlink[v] = dfstime++;
  stack[ss++] = v;
  for (int i = 0; i < edge[v].size(); ++i) {
    int w = edge[v][i];
    if (dfsin[w] < 0) { scc(w); lowlink[v] = min(lowlink[v], lowlink[w]); }
    else if (comp[w] < 0) lowlink[v] = min(lowlink[v], dfsin[w]);
  }
  
  if (dfsin[v] == lowlink[v]) {
    do {
      w = stack[--ss];
      comp[w] = ncomp;
    } while (w != v);
    ++ncomp;
  }
}

char alphabet[] = "AGTC";

int dist(char a, char b) {
  int p = strchr(alphabet, a) - alphabet, q = strchr(alphabet, b) - alphabet, d = abs(p - q);
  return min(d, 4 - d);
}

int main() {
  int subsets;
  char next[256];
  for (int i = 0; i < 4; ++i) next[alphabet[i]] = alphabet[(i + 1) % 4];
  while (scanf("%i%i", &n, &subsets), n) {
    numv = 4 * n;
    scanf("%s", str);

    for (int i = 0; i < numv; ++i) edge[i].clear();
    for (int i = 0; i < n - 1; ++i) 
      add_or(i, 0, i + 1, 0);                  // not x_i or not x_{i+1}
    for (int s = 0; s < subsets; ++s) {
      int size;
      scanf("%i:", &size);

      int v[size];
      for (int i = 0; i < size; ++i)
        scanf("%i", &v[i]);
      for (int i = 0, j = size - 1; i < j; ++i, --j) {
        int a = v[i], b = v[j], d = dist(str[a], str[b]);
        if (d == 0) {
          add_equal(a, b);                     // x_i = x_j
          add_equal(a + n, b + n);             // y_i = y_j
        } else if (d == 1) {
          add_distinct(a, b);                  // x_i != x_j
          bool rev = (str[b] != next[str[a]]);
          add_or(a, 1, b + n, rev);
          add_or(b, 1, a + n, rev ^ 1);
        } else {
          set(a, 1); set(b, 1);                // x_i = x_j = 1
          add_distinct(a + n, b + n);          // y_i != y_j
        }
      }
    }

    fill(&dfsin[0], &dfsin[numv], -1);
    fill(&comp[0], &comp[numv], -1);
    ncomp = dfstime = ss = 0;
    for (int i = 0; i < numv; ++i)
      if (dfsin[i] < 0) scc(i);

    bool possible = true;
    for (int i = 0; possible && i < numv; i += 2)
      if (comp[i] == comp[i + 1]) possible = false;
    puts(possible ? "YES" : "NO");
  }
  return 0;
}

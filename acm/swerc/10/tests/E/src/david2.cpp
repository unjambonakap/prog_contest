// A different, simpler O(n^2 + n * sets) solution to 'Palindromic DNA'. 
// It resembles the 2SAT solution but using a different graph with O(n^2) edges.
// David Garcia Soriano.
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

const int maxn = 10000;
int n;
char str[maxn + 1];

int parent[maxn], rank[maxn], first[maxn];

int find(int v) { return parent[v] == v ? v : parent[v] = find(parent[v]); }

void merge(int a, int b) {
  a = find(a); b = find(b);
  if (a != b) {
    if (rank[a] < rank[b]) parent[a] = b;
    else {
      parent[b] = a;
      if (rank[a] == rank[b]) ++rank[a];
    }
  }
}

char alphabet[] = "AGTC";
int index[256];

char sol[maxn + 1], sol2[maxn + 1];
bool possib[maxn][4];

vector<int> comp[maxn]; // comp[i] is a set of possitions that need to have equal characters

// Fix the 'i'th character to 'c' and follow all implications
bool dfs(int i, char c) {
  int rep = find(i);
  if (!possib[rep][index[(int)c]]) return false;

  bool visited = (sol[rep] != 0);
  if (visited) return sol[rep] == c;
  else {
    sol[rep] = c;
    for (int jj = 0; jj < comp[rep].size(); ++jj) {
      int j = comp[rep][jj];
      if (str[j] != c) {
        if (j > 0 && !dfs(j - 1, str[j - 1])) return false;
        if (j < n - 1 && !dfs(j + 1, str[j + 1])) return false;
      }
    }
  }
  return true;
}

bool is_solvable() {
  for (int i = 0; i < maxn; ++i) comp[i].clear();
  for (int i = 0; i < n; ++i)
    comp[find(i)].push_back(i); // all positions in comp[i] must end up with the same character

  // First determine which of the four letters are candidates for the value
  // of all positions within a component.
  for (int i = 0; i < n; ++i) if (!comp[i].empty()) {
    fill(&possib[i][0], &possib[i][4], true);
    for (int jj = 0; jj < comp[i].size(); ++jj) {
      int j = comp[i][jj], l = index[(int)str[j]];
      possib[i][(l + 2) % 4] = false;
    }
  }

  // Now try all possible 4 letters for each component and follow all implications.
  // By properties of 2SAT, if we can't find a contradiction with some value following
  // a chain of implications, we can fix this value and move on to the next component,
  // with no need for backtracking.
  for (int i = 0; i < n; ++i) if (!comp[i].empty() && !sol2[comp[i][0]]) {
    bool can = false;
    for (int l = 0; l < 4; ++l) if (possib[i][l]) {
      copy(&sol2[0], &sol2[n], &sol[0]);
      if (dfs(i, alphabet[l])) { can = true; break; }
    }
    if (!can) return false;

    // The following is only needed to store a possible solution in sol2[]
    for (int j = 0; j < n; ++j) if (sol[find(j)])
      sol2[j] = sol[find(j)];
  }
  return true;
}

int main() {
  int subsets;
  for (int i = 0; i < 4; ++i)
    index[(int)alphabet[i]] = i;
  while (scanf("%i%i", &n, &subsets), n) {
    scanf("%s", str);
    for (int i = 0; i < n; ++i) { parent[i] = i; rank[i] = 0; }

    for (int i = 0; i < subsets; ++i) {
      int size;
      scanf("%i:", &size);

      vector<int> v(size);
      for (int i = 0; i < size; ++i)
        scanf("%i", &v[i]);
      for (int i = 0, j = size - 1; i < j; ++i, --j) 
        merge(v[i], v[j]);
    }

    fill(&sol2[0], &sol2[n], 0);
    puts(is_solvable() ? "YES" : "NO");
  }
  return 0;
}

#include <cassert>
#include <cstdio>

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

unsigned long long lcg_seed;
unsigned lcg_rand( unsigned a, unsigned b ) {
  unsigned r = a + (unsigned)(lcg_seed >> 16) % (b - a + 1);
  lcg_seed = 239017 * lcg_seed + 301703;
  return r;
}

using namespace std;

vector <pair <int, int> > vertices;
set <pair <int, int> > edges;

bool edge( int i1, int i2 ) {
  if (max(i1, i2) >= (int)vertices.size() || i1 == i2)
    return false;
  pair <int, int> edge = make_pair(min(vertices[i1].first, vertices[i2].first), max(vertices[i1].first, vertices[i2].first));
  assert(edge.first != edge.second);
  if (edges.count(edge))
    return false;
  edges.insert(edge);
  if (!--vertices[i1].second) {
    vertices[i1] = vertices[vertices.size() - 1];
    if (i2 == (int)vertices.size() - 1)
      i2 = i1;
    vertices.pop_back();
  }
  if (!--vertices[i2].second) {
    vertices[i2] = vertices[vertices.size() - 1];
    vertices.pop_back();
  }
  return true;
}

int main( int argc, char **argv ) {
  assert(argc == 5 && "usage: ./gen_rand <n> <m> <k> <randseed>");
  int n = atoi(argv[1]);
  int m = atoi(argv[2]);
  int k = atoi(argv[3]);
  int count = 0;
  lcg_seed = _atoi64(argv[4]);
  assert(k >= 4 || k == n && k >= 3);

  for (int i = 0; i < k; i++) {
    edges.insert(make_pair(min(i, (i + 1) % k), max(i, (i + 1) % k)));
    if (k >= 4)
      vertices.push_back(make_pair(i, k - 3));
  }
  for (int i = k; i < n; i++) {
    int j = lcg_rand(0, vertices.size() - 1);
    vertices.push_back(make_pair(i, k - 1));
    assert(edge(j, vertices.size() - 1));
  }
  while ((int)edges.size() < m) {
    assert(vertices.size() >= 2);
    do {
      int j1 = lcg_rand(0, vertices.size() - 1);
      int j2 = lcg_rand(0, vertices.size() - 1);
      if (edge(j1, j2))
        break;
      assert(++count < 100 * (n + m + k));
    } while (true);
  }
  assert((int)edges.size() == m);

  int *p_v = new int[n];
  pair <int, int> *p_e = new pair<int, int>[m];
  for (int i = 0; i < n; i++) {
    p_v[i] = i + 1;
    if (i >= k) {
      int j = lcg_rand(k, i);
      swap(p_v[i], p_v[j]);
    }
  }
  int i = 0;
  for (set <pair <int, int> >::iterator it = edges.begin(); it != edges.end(); it++, i++) {
    p_e[i] = *it;
    if (lcg_rand(0, 1))
      swap(p_e[i].first, p_e[i].second);
    int j = lcg_rand(0, i);
    swap(p_e[i], p_e[j]);
  }

  printf("%d %d %d\n", n, k, m);
  for (int i = 0; i < m; i++)
    printf("%d %d\n", p_v[p_e[i].first], p_v[p_e[i].second]);

  return 0;
}

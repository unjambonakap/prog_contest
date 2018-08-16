// O(n log n + q * (log n)^2 * log(answer) ) solution to 'manhattan'
// David Garcia Soriano
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;

const int maxn = 100000;
typedef long long ll;
const ll infinity = (1ll << 60);

struct Point {
  ll x, y;
} v[maxn];

struct cmp_x {
  bool operator()(const Point& a, const Point& b) const {
    return a.x < b.x;
  }
};

struct cmp_y {
  bool operator()(const Point& a, const Point& b) const {
    return a.y < b.y;
  }
};

struct Node {
  Node *left, *right;
  int start, end;
  vector<Point> p;
} tree[2 * maxn];

int id;

// Builds a range tree in O(n (log n)^2)
Node* build_range_tree(int a, int b) {
  Node* r = &tree[id++];
  r->start = a; r->end = b;
  r->p.assign(&v[a], &v[b]);
  sort(r->p.begin(), r->p.end(), cmp_y());
  r->left = r->right = 0;
  if (b - a > 1) {
    int m = (a + b) / 2;
    r->left = build_range_tree(a, m);
    r->right = build_range_tree(m, b);
  }
  return r;
}

// Determine the existence of points in the range [x - d, x + d] x [y - d, y + d] in O((log n)^2)
bool find_points(ll x, ll y, ll d, Node* r) {
  if (!r) return false;
  ll min_x = v[r->start].x, max_x = v[r->end - 1].x;
  if (x + d < min_x || x - d > max_x) return false;

  if (x - d <= min_x && max_x <= x + d) {
    Point p; p.y = y - d;
    vector<Point>::const_iterator it = lower_bound(r->p.begin(), r->p.end(), p, cmp_y());
    return it != r->p.end() && it->y <= y + d;
  } else
    return find_points(x, y, d, r->left) || find_points(x, y, d, r->right);
}

int main() {
  int n, queries;
	bool first = true;
  while (scanf("%i", &n), n > 0) {
	  if (!first) printf("\n"); 
    first = false;

    for (int i = 0; i < n; ++i) {
      ll x, y;
      scanf("%lli%lli", &x, &y);
      v[i].x = x + y;
      v[i].y = x - y;
    }

    sort(&v[0], &v[n], cmp_x());
    id = 0; build_range_tree(0, n);
	  scanf("%i", &queries);
    while (queries--) {
      ll x, y, a, b;
      scanf("%lli%lli", &a, &b);
      x = a + b;
      y = a - b;

      if (find_points(x, y, 0, &tree[0])) b = 0;
      else {
        b = 1;
        while (!find_points(x, y, b, &tree[0])) b *= 2;
        a = b / 2;
        while (b - a != 1) {
          int m = (a + b) / 2;
          if (find_points(x, y, m, &tree[0])) b = m;
          else a = m;
        }
      }

      printf("%lli\n", b);
    }
  }

  return 0;
}

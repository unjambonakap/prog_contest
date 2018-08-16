#include <algorithm>
#include <cstdio>
#include <vector>
#include <map>
#include <set>

using namespace std;

const int kDefaultSpeed = 10;
const int kMaxAnswer = 2000000;

int main() {
  freopen("drive.in", "r", stdin);
  freopen("drive.out", "w", stdout);
  int xa;
  int ya;
  int xb;
  int yb;
  int n;
  scanf("%d %d %d %d %d", &xa, &ya, &xb, &yb, &n);
  vector<int> x1(n);
  vector<int> y1(n);
  vector<int> x2(n);
  vector<int> y2(n);
  vector<int> t(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d %d %d %d %d", &x1[i], &y1[i], &x2[i], &y2[i], &t[i]);
  }

  set<int> xs;
  set<int> ys;
  xs.insert(xa);
  xs.insert(xb);
  ys.insert(ya);
  ys.insert(yb);
  for (int i = 0; i < n; ++i) {
    xs.insert(x1[i]);
    xs.insert(x2[i]);
    ys.insert(y1[i]);
    ys.insert(y2[i]);
  }
  int nx = 0;
  int ny = 0;
  vector<int> xv;
  vector<int> yv;
  map<int, int> x_to_id;
  map<int, int> y_to_id;
  for (set<int>::const_iterator it = xs.begin(); it != xs.end(); ++it) {
    x_to_id[*it] = nx++;
    xv.push_back(*it);
  }
  for (set<int>::const_iterator it = ys.begin(); it != ys.end(); ++it) {
    y_to_id[*it] = ny++;
    yv.push_back(*it);
  }

  int field_size = nx * ny;
  vector<int> cost_right(field_size, -1);
  vector<int> cost_down(field_size, -1);
  for (int x = 0; x < nx; ++x)
    for (int y = 0; y < ny - 1; ++y) {
      cost_down[x * ny + y] = (yv[y + 1] - yv[y]) * kDefaultSpeed;
    }
  for (int x = 0; x < nx - 1; ++x)
    for (int y = 0; y < ny; ++y) {
      cost_right[x * ny + y] = (xv[x + 1] - xv[x]) * kDefaultSpeed;
    }
  for (int i = 0; i < n; ++i) {
    int cx1 = x_to_id[x1[i]];
    int cy1 = y_to_id[y1[i]];
    int cx2 = x_to_id[x2[i]];
    int cy2 = y_to_id[y2[i]];
    for (int x = cx1 + 1; x < cx2; ++x)
      for (int y = cy1; y < cy2; ++y) {
        cost_down[x * ny + y] = (yv[y + 1] - yv[y]) * t[i];
      }
    for (int x = cx1; x < cx2; ++x)
      for (int y = cy1 + 1; y < cy2; ++y) {
        cost_right[x * ny + y] = (xv[x + 1] - xv[x]) * t[i];
      }
  }

  int src = x_to_id[xa] * ny + y_to_id[ya];
  int dst = x_to_id[xb] * ny + y_to_id[yb];

  vector<int> next(field_size + kMaxAnswer + 1, -1);
  vector<int> prev(field_size + kMaxAnswer + 1, -1);
  vector<int> dist(field_size, kMaxAnswer);
  dist[src] = 0;
  for (int i = 0; i <= kMaxAnswer; ++i) {
    next[field_size + i] = field_size + i;
    prev[field_size + i] = field_size + i;
  }
  for (int i = 0; i < field_size; ++i) {
    int d = dist[i];
    next[i] = next[d + field_size];
    prev[i] = d + field_size;
    next[prev[i]] = i;
    prev[next[i]] = i;
  }

  for (int cur_dist = 0; cur_dist < kMaxAnswer; ++cur_dist) {
    int at = next[field_size + cur_dist];
    while (at < field_size) {
      int atx = at / ny;
      int aty = at % ny;
      if (atx < nx - 1) {
        int nxt = at + ny;
        int nxt_dist = cost_right[at] + cur_dist;
	if (nxt_dist < dist[nxt]) {
	  prev[next[nxt]] = prev[nxt];
	  next[prev[nxt]] = next[nxt];
	  dist[nxt] = nxt_dist;
	  next[nxt] = next[nxt_dist + field_size];
	  prev[nxt] = nxt_dist + field_size;
	  prev[next[nxt]] = nxt;
	  next[prev[nxt]] = nxt;
	}
      }
      if (atx > 0) {
        int nxt = at - ny;
        int nxt_dist = cost_right[nxt] + cur_dist;
	if (nxt_dist < dist[nxt]) {
	  prev[next[nxt]] = prev[nxt];
	  next[prev[nxt]] = next[nxt];
	  dist[nxt] = nxt_dist;
	  next[nxt] = next[nxt_dist + field_size];
	  prev[nxt] = nxt_dist + field_size;
	  prev[next[nxt]] = nxt;
	  next[prev[nxt]] = nxt;
	}
      }
      if (aty < ny - 1) {
        int nxt = at + 1;
        int nxt_dist = cost_down[at] + cur_dist;
	if (nxt_dist < dist[nxt]) {
	  prev[next[nxt]] = prev[nxt];
	  next[prev[nxt]] = next[nxt];
	  dist[nxt] = nxt_dist;
	  next[nxt] = next[nxt_dist + field_size];
	  prev[nxt] = nxt_dist + field_size;
	  prev[next[nxt]] = nxt;
	  next[prev[nxt]] = nxt;
	}
      }
      if (aty > 0) {
        int nxt = at - 1;
        int nxt_dist = cost_down[nxt] + cur_dist;
	if (nxt_dist < dist[nxt]) {
	  prev[next[nxt]] = prev[nxt];
	  next[prev[nxt]] = next[nxt];
	  dist[nxt] = nxt_dist;
	  next[nxt] = next[nxt_dist + field_size];
	  prev[nxt] = nxt_dist + field_size;
	  prev[next[nxt]] = nxt;
	  next[prev[nxt]] = nxt;
	}
      }
      at = next[at];
    }
  }

  printf("%d\n", dist[dst]);
  return 0;
}

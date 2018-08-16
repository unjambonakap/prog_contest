#include <algorithm>
#include <cstdio>
#include <vector>
#include <map>
#include <set>

using namespace std;

typedef long long Cost;

const Cost kDefaultSpeed = 10;
const Cost kMaxAnswer = 2000000000LL;

inline void HeapSwap(vector<Cost>& heap_val, vector<int>& heap, vector<int>& heap_at, int v1, int v2) {
  int t = heap[v1];
  heap[v1] = heap[v2];
  heap[v2] = t;
  Cost ct = heap_val[v1];
  heap_val[v1] = heap_val[v2];
  heap_val[v2] = ct;
  heap_at[heap[v1]] = v1;
  heap_at[heap[v2]] = v2;
}

inline void HeapDown(vector<Cost>& heap_val, vector<int>& heap, vector<int>& heap_at, int v, int num) {
  while (true) {
    int i = v;
    if (v * 2 + 1 < num && heap_val[v * 2 + 1] < heap_val[i]) {
      i = v * 2 + 1;
    }
    if (v * 2 + 2 < num && heap_val[v * 2 + 2] < heap_val[i]) {
      i = v * 2 + 2;
    }
    if (i == v) {
      break;
    }
    HeapSwap(heap_val, heap, heap_at, v, i);
    v = i;
  }
}

inline void HeapUp(vector<Cost>& heap_val, vector<int>& heap, vector<int>& heap_at, int v, int num) {
  while (v > 0) {
    int i = (v - 1) / 2;
    if (heap_val[v] < heap_val[i]) {
      HeapSwap(heap_val, heap, heap_at, v, i);
      v = i;
    } else {
      break;
    }
  }
}

inline void Reach(vector<Cost>& heap_val, vector<int>& heap, vector<int>& heap_at, vector<Cost>& dist, int& heap_num, int what, Cost cost) {
  if (dist[what] >= 0 && cost >= dist[what]) {
    return;
  }
  dist[what] = cost;
  if (heap_at[what] < 0) {
    heap[heap_num] = what;
    heap_at[what] = heap_num;
    heap_val[heap_num] = cost;
    ++heap_num;
  } else {
    heap_val[heap_at[what]] = cost;
  }
  HeapUp(heap_val, heap, heap_at, heap_at[what], heap_num);
}

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
  vector<Cost> t(n);
  for (int i = 0; i < n; ++i) {
    int t_int;
    scanf("%d %d %d %d %d", &x1[i], &y1[i], &x2[i], &y2[i], &t_int);
    t[i] = t_int;
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
  vector<Cost> cost_right(field_size, -1);
  vector<Cost> cost_down(field_size, -1);
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

  vector<Cost> heap_val(field_size, -1);
  vector<int> heap(field_size, -1);
  vector<int> heap_at(field_size, -1);
  vector<Cost> dist(field_size, -1);
  int heap_num = 1;
  heap_val[0] = 0;
  heap[0] = src;
  heap_at[src] = 0;
  dist[src] = 0;
  int max_heap_size = 1;
  
  while (true) {
    max_heap_size = max(max_heap_size, heap_num);
    int at = heap[0];
    Cost cur_dist = heap_val[0];
    if (at == dst) {
      break;
    }
    HeapSwap(heap_val, heap, heap_at, 0, heap_num - 1);
    --heap_num;
    HeapDown(heap_val, heap, heap_at, 0, heap_num);
    int atx = at / ny;
    int aty = at % ny;
    if (atx < nx - 1) {
      int nxt = at + ny;
      Cost nxt_dist = cost_right[at] + cur_dist;
      Reach(heap_val, heap, heap_at, dist, heap_num, nxt, nxt_dist);
    }
    if (atx > 0) {
      int nxt = at - ny;
      Cost nxt_dist = cost_right[nxt] + cur_dist;
      Reach(heap_val, heap, heap_at, dist, heap_num, nxt, nxt_dist);
    }
    if (aty < ny - 1) {
      int nxt = at + 1;
      Cost nxt_dist = cost_down[at] + cur_dist;
      Reach(heap_val, heap, heap_at, dist, heap_num, nxt, nxt_dist);
    }
    if (aty > 0) {
      int nxt = at - 1;
      Cost nxt_dist = cost_down[nxt] + cur_dist;
      Reach(heap_val, heap, heap_at, dist, heap_num, nxt, nxt_dist);
    }
  }

  printf("%d\n", (int) dist[dst]);
  fprintf(stderr, "Max heap size: %d\n", max_heap_size);
  return 0;
}

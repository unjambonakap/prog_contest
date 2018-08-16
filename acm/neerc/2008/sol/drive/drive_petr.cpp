#include <algorithm>
#include <cstdio>
#include <vector>
#include <map>
#include <set>

using namespace std;

typedef long long Cost;

const int kDefaultSpeed = 10;
const Cost kMaxAnswer = 2000000000LL;
const int kMaxN = 1000;
const int kMaxCoord = 100000000;
const int kMaxSpeed = 100000000;

inline int SolveOneDirection(vector<int>& x1, vector<int>& y1, vector<int>& x2, vector<int>& y2, vector<int>& t, int n, int xa, int ya, int xb, int yb, int nx, int ny, vector<int>& xv, vector<int>& yv) {
  vector<Cost> d(ny, kMaxAnswer);
  if (xa > xb) {
    int t = xa;
    xa = xb;
    xb = t;
    t = ya;
    ya = yb;
    yb = t;
  }
  d[ya] = 0;
  for (int x = xa; x <= xb; ++x) {
    if (x > xa) {
      vector<int> delta(ny, kDefaultSpeed);
      for (int i = 0; i < n; ++i) {
      	if (x1[i] <= x - 1 && x2[i] >= x) {
	  for (int j = y1[i] + 1; j < y2[i]; ++j) {
	    delta[j] = t[i];
	  }
	}
      }
      for (int i = 0; i < ny; ++i) {
        d[i] = min(kMaxAnswer, d[i] + (Cost) delta[i] * (xv[x] - xv[x - 1]));
      }
    }
    {
      vector<int> delta(ny - 1, kDefaultSpeed);
      for (int i = 0; i < n; ++i) {
        if (x1[i] < x && x2[i] > x) {
	  for (int j = y1[i]; j < y2[i]; ++j) {
	    delta[j] = t[i];
	  }
	}
      }
      for (int i = 0; i < ny - 1; ++i) {
        d[i + 1] = min(d[i + 1], d[i] + (Cost) delta[i] * (yv[i + 1] - yv[i]));
      }
      for (int i = ny - 1; i > 0; --i) {
        d[i - 1] = min(d[i - 1], d[i] + (Cost) delta[i - 1] * (yv[i] - yv[i - 1]));
      }
    }
  }
  return (int) d[yb];
}

int main() {
  freopen("drive.in", "r", stdin);
  freopen("drive.out", "w", stdout);
  int xa;
  int ya;
  int xb;
  int yb;
  int n;
  scanf("%d %d %d %d %d\n", &xa, &ya, &xb, &yb, &n);
  if (n < 0 || n > kMaxN || xa < 0 || xa > kMaxCoord || ya < 0 || ya > kMaxCoord || xb < 0 || xb > kMaxCoord || yb < 0 || yb > kMaxCoord || xa == xb && ya == yb) {
    exit(1);
  }
  vector<int> x1(n);
  vector<int> y1(n);
  vector<int> x2(n);
  vector<int> y2(n);
  vector<int> t(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d %d %d %d %d\n", &x1[i], &y1[i], &x2[i], &y2[i], &t[i]);
    if (t[i] <= kDefaultSpeed || t[i] > kMaxSpeed || x1[i] < 0 || x2[i] <= x1[i] || x2[i] > kMaxCoord || y1[i] < 0 || y2[i] <= y1[i] || y2[i] > kMaxCoord) {
      exit(1);
    }
  }

  for (int i = 0; i < n; ++i) {
    if (xa >= x1[i] && xa <= x2[i] && ya >= y1[i] && ya <= y2[i])
      exit(1);
    if (xb >= x1[i] && xb <= x2[i] && yb >= y1[i] && yb <= y2[i])
      exit(1);

    for (int j = i + 1; j < n; ++j) {
      if (x2[i] < x1[j] || x2[j] < x1[i] || y2[i] < y1[j] || y2[j] < y1[i])
      	continue;
      exit(1);
    }
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
  xa = x_to_id[xa];
  ya = y_to_id[ya];
  xb = x_to_id[xb];
  yb = y_to_id[yb];
  for (int i = 0; i < n; ++i) {
    x1[i] = x_to_id[x1[i]];
    y1[i] = y_to_id[y1[i]];
    x2[i] = x_to_id[x2[i]];
    y2[i] = y_to_id[y2[i]];
  }

  int res_by_x = SolveOneDirection(x1, y1, x2, y2, t, n, xa, ya, xb, yb, nx, ny, xv, yv);
  int res_by_y = SolveOneDirection(y1, x1, y2, x2, t, n, ya, xa, yb, xb, ny, nx, yv, xv);
  int res = min(res_by_x, res_by_y);
  printf("%d\n", res);

  return 0;
}

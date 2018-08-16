// O(n log n) divide and conquer solution to balance.
// Assumes all points have distinct x coordinates.
// David Garcia Soriano.
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;

const int maxn = 50000;
const double eps = 1e-11, infinity = 1e300;

struct Point { 
  double x, y; 
  bool operator<(const Point& b) const { return  x < b.x; }
};
Point point[maxn];
double sqrrad[maxn];

double yparab(int i, double x) {
  double dx = x - point[i].x;
  return dx * dx + point[i].y * point[i].y;
}

double xintersect(int i, int j) {
  return (sqrrad[j] - sqrrad[i]) / (2 * (point[j].x - point[i].x));
}

void beachline(int a, int b, vector<double>& pos, vector<int>& parab) {
  pos.clear();
  parab.clear();
  if (b <= a) return;
  if (b - a == 1) {
    pos.push_back(-infinity); pos.push_back(infinity);
    parab.push_back(a);
    return;
  }

  int m = (a + b) / 2;
  vector<double> leftpos, rightpos;
  vector<int> leftparab, rightparab;
  beachline(a, m, leftpos, leftparab);
  beachline(m, b, rightpos, rightparab);

  int i = 0, j = 0;
  double x = -infinity;
  while (x < infinity) {
    assert(i < leftparab.size() && j < rightparab.size() && leftparab[i] <= rightparab[j]);

    pos.push_back(x);   
    double nextx = min(leftpos[i + 1], rightpos[j + 1]),
           xint = xintersect(leftparab[i], rightparab[j]);
   
    if (xint <= x + eps) { 
      parab.push_back(leftparab[i]); 
    } else if (xint >= nextx - eps) { 
      parab.push_back(rightparab[j]); 
    } else {
      parab.push_back(rightparab[j]);
      pos.push_back(xint);
      parab.push_back(leftparab[i]);
    }

    x = nextx;
    if (nextx == leftpos[i + 1]) ++i;
    else ++j;
  }
  pos.push_back(infinity);
}

void check(int i, double x, double& bestx, double& miny) {
  double y = yparab(i, x);
  if (y < miny) {
    miny = y;
    bestx = x;
  }
}

int main() {
  int n;
  while (scanf("%i", &n) == 1 && n > 0) {
    for (int i = 0; i < n; ++i)
      scanf("%lf%lf", &point[i].x, &point[i].y);
    sort(&point[0], &point[n]);
    for (int i = 0; i < n; ++i)
      sqrrad[i] = point[i].x * point[i].x + point[i].y * point[i].y;

    vector<double> pos;
    vector<int> parab;
    beachline(0, n, pos, parab);

    double miny = infinity, bestx;
    for (int i = 0; i < parab.size(); ++i) {
      if (i > 0)
        check(parab[i], pos[i], bestx, miny);
      if (point[parab[i]].x >= pos[i] && point[parab[i]].x <= pos[i + 1]) 
        check(parab[i], point[parab[i]].x, bestx, miny);
    }
    printf("%.9lf %.9lf\n", bestx, sqrt(miny));
  }
  return 0;
}

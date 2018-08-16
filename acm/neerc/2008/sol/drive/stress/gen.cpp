#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

const int kMinWidth = 10;
const int kMinHeight = 7;
const int kMaxWidth = 25;
const int kMaxHeight = 15; 
const int kMaxN = 15;

long long rdtsc() { asm {
  rdtsc
} }

int main() {
  unsigned seed = rdtsc();
  cerr << "R " << seed << endl;
  srandom(seed);
  random();
  random();
  random();
  int n = 0;
  vector<int> x1(n);
  vector<int> y1(n);
  vector<int> x2(n);
  vector<int> y2(n);
  int xa;
  int ya;
  int xb;
  int yb;
  while (true) {
  n = random() % kMaxN + 1;
  x1.resize(n);
  y1.resize(n);
  x2.resize(n);
  y2.resize(n);
  int width = kMinWidth + random() % (kMaxWidth - kMinWidth);
  int height = kMinHeight + random() % (kMaxHeight - kMinHeight);
  int ctr = 0;
  while (ctr < 20) {
    ++ctr;
    bool ok = true;
    for (int i = 0; i < n; ++i) {
      bool any = false;
      for (int tr = 0; tr < 1000; ++tr) {
        x1[i] = random() % width;
        y1[i] = random() % height;
        x2[i] = random() % width;
        y2[i] = random() % height;
        if (x1[i] >= x2[i] || y1[i] >= y2[i])
	  continue;
	bool cok = true;
        for (int j = 0; j < i; ++j) {
          if (x1[i] > x2[j] || x1[j] > x2[i] || y1[i] > y2[j] || y1[j] > y2[i]) continue;
	  cok = false;
	  break;
        }
	if (!cok)
	  continue;
	any = true;
	break;
      }
      if (!any) {
        ok = false;
	break;
      }
    }
    if (!ok)
      continue;
    ok = false;
    for (int tr = 1; tr < 1000; ++tr) {
      xa = random() % width;
      ya = random() % height;
      int cok = true;
      for (int i = 0; i < n; ++i) {
        if (xa < x1[i] || xa > x2[i] || ya < y1[i] || ya > y2[i]) continue;
	cok = false;
	break;
      }
      if (cok) {
        ok = true;
	break;
      }
    }
    if (!ok) continue;
    ok = false;
    for (int tr = 1; tr < 1000; ++tr) {
      xb = random() % width;
      yb = random() % height;
      if (xa == xb && ya == yb) continue;
      int cok = true;
      for (int i = 0; i < n; ++i) {
        if (xb < x1[i] || xb > x2[i] || yb < y1[i] || yb > y2[i]) continue;
	cok = false;
	break;
      }
      if (cok) {
        ok = true;
	break;
      }
    }
    if (!ok) continue;
    
    break;
  }

  if (ctr < 20) break;
  }

  cout << xa << " " << ya << " " << xb << " " << yb << endl << n << endl;
  for (int i = 0; i < n; ++i) {
    cout << x1[i] << " " << y1[i] << " " << x2[i] << " " << y2[i] << " " << rand() % 20 + 11 << endl;
  }
}

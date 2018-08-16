#include "testlib.h"

const int minN = 4;
const int maxN = 5000;
const int maxX = 100000000;

int n, x[maxN + 2], y[maxN + 2];

int main() {
  registerValidation();
  n = inf.readInt(minN, maxN);
  inf.readEoln();
  for (int i = 0; i < n; i++) {
    x[i] = inf.readInt(-maxX, maxX);
    inf.readSpace();
    y[i] = inf.readInt(-maxX, maxX);
    inf.readEoln();
  }
  inf.readEof();
  x[n] = x[0];
  y[n] = y[0];
  x[n + 1] = x[1];
  y[n + 1] = y[1];
  bool isPos = false, isNeg = false;
  for (int i = 0; i < n; i++) {
    long long x1, y1, x2, y2;
    x1 = x[i + 1] - x[i];
    y1 = y[i + 1] - y[i];
    x2 = x[i + 2] - x[i];
    y2 = y[i + 2] - y[i];
    long long p = x1 * y2 - x2 * y1;
    if (p > 0) {
      isPos = true;
    } else if (p < 0) {
      isNeg = true;
    } else {
      ensure(false);
    }
  }
  ensure(!isPos || !isNeg);
  return 0;
}

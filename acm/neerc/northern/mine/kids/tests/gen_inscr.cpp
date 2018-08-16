#include <cstdio>
#include <cassert>
#include <cstdlib>
#define _USE_MATH_DEFINES
#include <cmath>

#include "random.h"

const int maxN = 5000;

int a[maxN];

int main( int argc, char *argv[] ) {
  assert(argc == 4);
  int n = atoi(argv[1]);
  int r = atoi(argv[2]);
  initrand(atoi(argv[3]));
  int sum = 0;
  for (int i = 0; i < n; i++) {
    a[i] = R(maxN, 10 * maxN);
    sum += a[i];
    a[i] += a[i - 1];
  }
  printf("%d\n", n);
  for (int i = 0; i < n; i++) {
    double z = a[i] * 2 * M_PI / sum;
    int x = (int)(r * cos(z) + 0.5);
    int y = (int)(r * sin(z) + 0.5);
    printf("%d %d\n", x, y);
  }
  return 0;
}

// Solution to restaurant.
// If there are n lines and m plates being moved,
// outputs at most 3n lines with at most 1.5m plate movements.
// David Garcia Soriano.
#include <algorithm>
#include <cassert>
#include <cstdio>
using namespace std;

const int in = 0, out = 1;
int pile[2] = {};

void drop(int m) {
  if (m) printf("DROP %i %i\n", in + 1, m);
  pile[in] += m;
}

void take(int m) { 
  if (m) printf("TAKE %i %i\n", out + 1, m); 
  assert(pile[out] >= m);
  pile[out] -= m;
}

void move() {
  if (pile[in]) printf("MOVE %i->%i %i\n", in + 1, out + 1, pile[in]);
  pile[out] += pile[in];
  pile[in] = 0;
}

int main() {
  int n, ncase = 0;
  while (scanf("%i", &n) == 1 && n != 0) {
    if (ncase++) puts("");
    pile[0] = pile[1] = 0;
    while (n--) {
      char cad[100];
      int times;
      scanf("%s %i", cad, &times);
      if (cad[0] == 'D') drop(times);
      else {
        int t = min(pile[out], times);
        take(t); times -= t;
        if (times != 0) { 
          move();
          take(times);
        }
      }
    }
  }
  return 0;
}

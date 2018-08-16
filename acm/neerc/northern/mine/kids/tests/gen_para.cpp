#include <cstdio>
#include <cassert>
#include <cstdlib>

int main( int argc, char *argv[] ) {
  assert(argc == 4);
  int n = atoi(argv[1]);
  int a = atoi(argv[2]);
  int k = atoi(argv[3]);
  printf("%d\n", n);
  for (int i = 0; i < n; i++) {
    printf("%d %d\n", k * i, (i - a) * (i - a));
  }
  return 0;
}

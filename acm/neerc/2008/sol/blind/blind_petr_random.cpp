#include <cstdlib>
#include <cstdio>

using namespace std;

int main() {
  srand(43154731);
  char ans[10];
  char* moves[] = {"NORTH", "SOUTH", "EAST", "WEST"};
  for (int i = 0; i < 100000; ++i) {
    printf("%s\n", moves[rand() & 3]);
    fflush(stdout);
    gets(ans);
  }
  printf("DONE\n");
}

// Alternate solution to labyrinth.
// Bellman-Ford, O((W·H)^2).
#include <cstdio>
#include <deque>
#include <vector>
using namespace std;

const int infinity = 1000000000;

struct state {
  int x, y, t;
  state(int a = 0, int b = 0, int c = 0) : x(a), y(b), t(c) {}
};

const int maxn = 50;
int type[maxn][maxn], dist[maxn][maxn], level[maxn][maxn];
bool inqueue[maxn][maxn];
state dest[maxn][maxn];

typedef pair<int, int> cell;
deque<cell> q;

void addstate(int x, int y, int t) {
  if (dist[x][y] > t) {
    dist[x][y] = t;
    if (!inqueue[x][y]) {
      ++level[x][y];
      inqueue[x][y] = true;
      q.push_back(cell(x, y));
    }
  }
}

int main() {
  int ly, lx;
  while (scanf("%i%i", &lx, &ly) == 2 && lx) {
    fill(&dist[0][0], &dist[lx][0], infinity);
    fill(&type[0][0], &type[lx][0], 0);
    fill(&inqueue[0][0], &inqueue[lx][0], false);
    fill(&level[0][0], &level[lx][0], 0);

    int gravestones;
    scanf("%i", &gravestones);
    while (gravestones--) {
      int x, y;
      scanf("%i%i", &x, &y);
      type[x][y] = 1;
    }

    int holes;
    scanf("%i", &holes);
    while (holes--) {
      int x1, y1, x2, y2, t;
      scanf("%i%i%i%i%i", &x1, &y1, &x2, &y2, &t);
      type[x1][y1] = 2;
      dest[x1][y1] = state(x2, y2, t);
    }

    q.clear();
    addstate(0, 0, 0);
    bool loop = false;
    while (!q.empty()) {
      if (dist[0][0] < 0) { loop = true; break; } // not really necessary, but to beat Luis's time
      cell c = q.front(); q.pop_front();
      int x = c.first, y = c.second, t = dist[x][y];
      inqueue[x][y] = false;
      if (level[x][y] > ly * lx) { loop = true; break; }

      if (x == lx - 1 && y == ly - 1) continue;
      if (type[x][y] == 2) {
        addstate(dest[x][y].x, dest[x][y].y, dest[x][y].t + t);
      }
      else {
        int dx[] = { 1, 0, -1, 0 },
            dy[] = { 0, 1, 0, -1 };
        for (int mov = 0; mov < 4; ++mov) {
          int a = x + dx[mov], b = y + dy[mov];
          if (a >= 0 && a < lx && b >= 0 && b < ly && type[a][b] != 1)
            addstate(a, b, t + 1);
        }
      }
    }
    if (loop) puts("Never");
    else if (dist[lx - 1][ly - 1] == infinity) puts("Impossible");
    else printf("%i\n", dist[lx - 1][ly - 1]);
  }
  return 0;
}

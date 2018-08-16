#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

const int kMaxSize = 100;
bool visited[kMaxSize * 2 + 1][kMaxSize * 2 + 1];

bool move(string dir) {
  cout << dir << endl;
  string res;
  cin >> res;
  if (res == "BLOCKED")
    return false;
  else if (res == "EMPTY")
    return true;
  else
    exit(1);
}

void doit(int x, int y) {
  if (visited[x][y])
    return;
  visited[x][y] = true;
  if (move("NORTH")) {
    doit(x + 1, y);
    if (!move("SOUTH")) exit(1);
  }
  if (move("SOUTH")) {
    doit(x - 1, y);
    if (!move("NORTH")) exit(1);
  }
  if (move("EAST")) {
    doit(x, y + 1);
    if (!move("WEST")) exit(1);
  }
  if (move("WEST")) {
    doit(x, y - 1);
    if (!move("EAST")) exit(1);
  }
}

int main() {
  doit(kMaxSize, kMaxSize);
  cout << "DONE" << endl;
}

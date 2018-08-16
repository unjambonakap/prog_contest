#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef vector<string> VS;
typedef vector<int> VI;

VS city;
int get(const string& s) {
  for (int i = 0; i < city.size(); i++) if (city[i] == s) return i;
  city.push_back(s);
  return city.size()-1;
}

int d[51][51];
int nr[51][51], rd[51][51], R;
VI Rx, Ry, Rd;

double nroute[51][51];
double doit(int x, int y) {
  double& ret = nroute[x][y];
  if (ret != 0) return ret;
  if (x == y) return ret = 1;
  for (int i = 0; i < R; i++) if (x == Rx[i] && rd[Rx[i]][Ry[i]] == Rd[i]) {
    if (Rd[i] + d[Ry[i]][y] == d[x][y]) {
      ret += doit(Ry[i], y);
    }
  }
  return ret;
}

main() {
  int N, prob = 1;
  string s;
  for(cin >> N; N--;) {
    cin >> R >> s;
    city.clear();
    get(s);
    memset(d, 60, sizeof(d));
    memset(rd, 60, sizeof(rd));
    memset(nr, 0, sizeof(R));
    Rx.clear(); Ry.clear(); Rd.clear();
    for (int i = 0; i < R; i++) {
      int x, y, ln;
      cin >> s; x = get(s);
      cin >> s; y = get(s);
      cin >> ln;
      Rx.push_back(x); Ry.push_back(y); Rd.push_back(ln);
      if (ln < rd[x][y]) {
        d[x][y] = rd[x][y] = ln;
        nr[x][y] = 1;
      } else if (ln == rd[x][y]) {
        nr[x][y]++;
      }
    }
    for (int i = 0; i < city.size(); i++) d[i][i] = 0;
    for (int k = 0; k < city.size(); k++)
    for (int i = 0; i < city.size(); i++)
    for (int j = 0; j < city.size(); j++)
      d[i][j] <?= d[i][k] + d[k][j];
    memset(nroute, 0, sizeof(nroute));
    int nreachable = 0;
    vector<double> Rp(R, 0.0);
    for (int dest = 0; dest < city.size(); dest++)
    if (dest != 0 && d[0][dest] < 100000000) {
      nreachable++;
      for (int i = 0; i < R; i++) if (rd[Rx[i]][Ry[i]] == Rd[i]) {
        if (d[0][Rx[i]] + Rd[i] + d[Ry[i]][dest] == d[0][dest]) {
          Rp[i] += doit(0, Rx[i]) * doit(Ry[i], dest) / doit(0, dest);
        }
      }
    }
    printf("Case #%d:", prob++);
    for (int i = 0; i < R; i++) printf(" %.7lf", Rp[i] / nreachable);
    printf("\n");
  }
}

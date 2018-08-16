#include <algorithm>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <vector>
using namespace std;
#define FOR(i,n) for(int i=0;i<n;i++)
#define FORI(i,v) FOR(i,(int)v.size())
#define BEND(v) v.begin(),v.end()

const double eps = 1e-8;
int cas=0;
int lis(const vector<int>& xs) {
  vector<int> lis;

  FORI(i,xs) {
    vector<int>::iterator it = lower_bound(BEND(lis), xs[i]);
    if (it == lis.end()) lis.push_back(xs[i]);
    else *it = xs[i];
  }

  return lis.size();
}
void tests() {
  vector<int> xs;
  xs.push_back(1);
  xs.push_back(2);
  xs.push_back(3);
  assert(lis(xs) == 3);
  xs.push_back(3);
  assert(lis(xs) == 3);
  xs.push_back(4);
  assert(lis(xs) == 4);
}
void doit() {
  char buf[1024];
  scanf(" %[^\n]",buf);
  istringstream iss(buf);
  vector<string> ps;
  string p;
  while (iss >> p) ps.push_back(p);

  int P = ps.size();
  vector<int> xs;
  FOR(i,P) {
    int x; scanf("%d",&x);
    xs.push_back(x);
  }

  vector<string> ret;
  vector<string> sps = ps; sort(BEND(sps));
  FORI(i,sps) {
    int j=-1;
    FORI(k,ps) if (ps[k] == sps[i]) j = k;
    assert(j != -1);

    vector<int> xsp;
    vector<string> psp;
    FORI(k,xs) if (k != j) xsp.push_back(xs[k]);
    FORI(k,ps) if (k != j) psp.push_back(ps[k]);

    if (lis(xs) == lis(xsp)) {
      xs = xsp;
      ps = psp;
      ret.push_back(sps[i]);
    }
  }

  printf("Case #%d:",++cas);
  FORI(i,ret) printf(" %s",ret[i].c_str());
  printf("\n");
}
int main() {
  tests();
  int N;
  scanf("%d",&N);
  while (N --> 0) doit();
}

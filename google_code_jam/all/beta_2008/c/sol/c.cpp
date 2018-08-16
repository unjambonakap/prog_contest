#include <cstdio>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <stack>
#include <list>
#include <queue>
#include <deque>
#include <cctype>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <numeric>
#include <cmath>
using namespace std;

typedef vector <int > VI;
typedef vector < VI > VVI;
typedef long long LL;
typedef vector < LL > VLL;
typedef vector < double > VD;
typedef vector < string > VS;
typedef pair<int,int> PII;
typedef vector <PII> VPII;
typedef istringstream ISS;
typedef long double LD;

#define ALL(x) x.begin(),x.end()
#define REP(i,n) for (int i=0; i<(n); ++i)
#define FOR(var,pocz,koniec) for (int var=(pocz); var<=(koniec); ++var)
#define FORD(var,pocz,koniec) for (int var=(pocz); var>=(koniec); --var)
#define FOREACH(it, X) for(__typeof((X).begin()) it = (X).begin(); it != (X).end(); ++it)
#define PB push_back
#define PF push_front
#define MP(a,b) make_pair(a,b)
#define ST first
#define ND second
#define SIZE(x) (int)x.size()

map<string, int> mapa;
string pocz_s;
int pocz;
int n;

const int N = 110;
LD wyn[N];
int graf[200][200];
vector<int> nums[200][200];
int dist[200][200];
const int INF = 100*1000*1001;

int dodmapa(string &s){
  int w;
  if (mapa.count(s)) w = mapa[s];
  else{
    w = SIZE(mapa);
    mapa[s] = w;
  }
  return w;
}

LL cnt_sc[N][N];

void licz_cnt(int id){
  REP(i, n) cnt_sc[id][i] = 0LL;
  cnt_sc[id][id] = 1LL;
  VPII v;
  REP(i, n) v.PB(MP(dist[id][i], i));
  sort(ALL(v));
  FOREACH(it, v)
    if (it->ST < INF)
      REP(i, n)
        if (i != it->ND && dist[id][i] == it->ST + graf[it->ND][i] && dist[id][i] < INF)
          cnt_sc[id][i] += cnt_sc[id][it->ND] * (LL)SIZE(nums[it->ND][i]);
}


int main(){
  int te;
  cin >> te;
  FOR(nr, 1, te){
    printf("Case #%d: ", nr);
    REP(i, N) REP(j, N){
      graf[i][j] = dist[i][j] = i==j?0:INF;
      nums[i][j].clear();
    }
    REP(i, N) wyn[i] = (LD)0;
    int m;
    cin >> m >> pocz_s;
    mapa.clear();
    pocz = dodmapa(pocz_s);
    REP(i, m){
      string as, bs; int a, b, c;
      cin >> as >> bs >> c;
      a = dodmapa(as);
      b = dodmapa(bs);
      if (graf[a][b] > c){
        graf[a][b] = c;
        nums[a][b].clear();
      }
      if (graf[a][b] == c)
        nums[a][b].PB(i);
    }
    n = SIZE(mapa);
    REP(i, n) REP(j, n) dist[i][j] = graf[i][j];
    REP(k, n) REP(i, n) REP(j, n)
      dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    REP(i, n)
      licz_cnt(i);
/*    REP(i, n)
      REP(j, n)
        printf("(%d -> %d): dist = %d, cnt = %lld\n", i, j, dist[i][j], cnt_sc[i][j]);*/
    int dupa = 0;
    REP(a, n) if (a != pocz){
      LL mian = cnt_sc[pocz][a];
      if (dist[pocz][a] >= INF || mian == 0LL) continue;
      dupa++;
      REP(i, n) REP(j, n)
        if (graf[i][j] < INF && dist[pocz][i] + graf[i][j] + dist[j][a] == dist[pocz][a])
          FOREACH(it, nums[i][j]){
            wyn[*it] += (LD)cnt_sc[pocz][i] * (LD)cnt_sc[j][a] / (LD)mian;
          }
    }
    REP(i, m) wyn[i] /= (LD)dupa;
    REP(i, m) printf(" %.07Lf", wyn[i]);
    printf("\n");
  }

	return 0;
}

#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <climits>
//#include <ext/hash_map>
#include <fstream>
#include <unordered_map>
#include <unordered_set>

// clang-format off

using namespace std;
using namespace __gnu_cxx;



#define REP(i,n) for(int i = 0; i < int(n); ++i)
#define REPV(i, n) for (int i = (n) - 1; (int)i >= 0; --i)
#define FOR(i, a, b) for(int i = (int)(a); i < (int)(b); ++i)

#define FE(i,t) for (__typeof((t).begin())i=(t).begin();i!=(t).end();++i)
#define FEV(i,t) for (__typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();++i)

#define two(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()


#define pb push_back
#define ST first
#define ND second
#define MP(x,y) make_pair(x, y)

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef signed long long s64;
typedef unsigned long long u64;

template<class T> void checkmin(T &a, T b){if (b<a)a=b;}
template<class T> void checkmax(T &a, T b){if (b>a)a=b;}
template<class T> void out(T t[], int n){REP(i, n)cout<<t[i]<<" "; cout<<endl;}
template<class T> void out(vector<T> t, int n=-1){for (int i=0; i<(n==-1?t.size():n); ++i) cout<<t[i]<<" "; cout<<endl;}
inline int count_bit(int n){return (n==0)?0:1+count_bit(n&(n-1));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}
const int maxn=11111;

// clang-format on

struct Reaction {
  std::vector<int> out;
  int needed;
};

std::unordered_map<int, std::vector<int> > chem_to_reaction;
std::vector<Reaction> reactions;
std::unordered_set<int> has;

void get_nums(const char *s, vector<int> &out) {
  std::istringstream ss(s);
  int v;
  while (ss >> v) {
    out.push_back(v);
  }
}

void go(int v){
  if (has.count(v)) return;
  has.insert(v);
  for (auto &rid : chem_to_reaction[v]){
    auto &r = reactions[rid];
    if (--r.needed==0){
      for (auto &x : r.out) go(x);
    }
  }

}

int main() {
  vector<string> lines;
  for (string l; std::getline(cin, l);) {
    lines.push_back(l);
  }

  vector<int> init;
  get_nums(lines[0].data(), init);

  FOR (i, 1, lines.size()) {
    auto &cur = lines[i];
    int mid = cur.find('-');
    cur[mid] = 0;
    vector<int> in, out;
    get_nums(cur.data(), in);
    get_nums(cur.data() + mid + 2, out);
    reactions.emplace_back(Reaction {out, (int)in.size()});
    for (auto &e : in) chem_to_reaction[e].push_back(i-1);
  }

  for (auto &e : init) go(e);
  std::vector<int> res(ALL(has));
  out(res);

  return 0;
}

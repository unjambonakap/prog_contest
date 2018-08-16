// BEGIN CUT HERE

// END CUT HERE
#line 5 "MonsterFarm.cpp"

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


using namespace std;
using namespace __gnu_cxx;



#define REP(i,n) for(int i = 0; i < int(n); ++i)
#define FOR(i, a, b) for(int i = (int)(a); i < (int)(b); ++i)
#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();++i)

#define two(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()


#define pb push_back
#define ST first
#define ND second
#define MP(x,y) make_pair(x, y)

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;

template<class T> void checkmin(T &a, T b){if (b<a)a=b;}
template<class T> void checkmax(T &a, T b){if (b>a)a=b;}
template<class T> void out(T t[], int n){REP(i, n)cout<<t[i]<<" "; cout<<endl;}
template<class T> void out(vector<T> t, int n=-1){for (int i=0; i<(n==-1?t.size():n); ++i) cout<<t[i]<<" "; cout<<endl;}
inline int count_bit(int n){return (n==0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int maxn=55;
const int mod=1e9+7;

int n;
int g[maxn][maxn];
int dp[maxn];
int vis[maxn];
int scc[maxn];
int deg[maxn];
vi tba;
vi tbb;

void dfsa(int a){
    if (vis[a]) return;
    vis[a]=1;
    REP(i,n) if (g[a][i]) dfsa(i);
    tba.pb(a);
}

void dfsb(int a){
    if (vis[a]) return;
    vis[a]=1;
    REP(i,n) if (g[i][a]) dfsb(i);
    tbb.pb(a);
}

int proc(int a){
    int &r=dp[scc[a]];
    if (r!=-1) return r;
    int fd=0;
    int nx=0;

    REP(i,n) if (scc[i]==scc[a]) checkmax(fd,deg[i]), ++nx;
    if (nx>1&&fd>1) return r=-2;
    if (nx>1) return r=1;

    r=0;
    REP(i,n) if (g[a][i]){
        if (i==a) return r=fd==1?1:-2;
        int res=proc(i);
        if (res==-2) return r=-2;
        r=(r+1ll*g[a][i]*res)%mod;;
    }
    return r;
}

class MonsterFarm {
	public:
	int numMonsters(vector <string> transforms) {
        n=transforms.size();
        memset(g,0,sizeof(g));
        REP(i, n){
            istringstream ss(transforms[i]);
            int a; while(ss>>a) ++g[i][a-1];
            
        }
        memset(deg,0,sizeof(deg));
        REP(i,n) REP(j,n) deg[i]+=g[i][j];



        tba.clear();
        memset(vis,0,sizeof(vis));
        dfsa(0);
        REP(i,n) REP(j,n) if (!vis[j]||!vis[i]) g[j][i]=g[i][j]=0;
        REP(i,n) if (!vis[i]) scc[i]=-1;
        memset(vis,0,sizeof(vis));
        int cnt=0;
        for (int i=tba.size()-1; i>=0; --i) if (!vis[tba[i]]){
            tbb.clear();
            dfsb(tba[i]);
            FE(it, tbb) scc[*it]=cnt;
            ++cnt;
        }

        memset(dp,-1,sizeof(dp));
        int res=proc(0);
        return res==-2?-1:res;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	//void test_case_0() { string Arr0[] = {"1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, numMonsters(Arg0)); }
	void test_case_0() { string Arr0[] = {"11 31 8 16 2 24 8 4 43", "42", "27 10 49 8 6 14 43 48 18 49 7 8 43 49", "9 30 18 42 22 44 36 22 42 47 29 49 41 22 8 22", "5", "33 29 2 42 14", "7", "14", "9", "2", "48", "48", "22 8 3 32 47", "2 46 12 18", "33 14 47 12 3 49 49 46 27 43 49 12 43 4 21", "9", "25", "47 47 44 44 44 22 46 47 47", "5 3 7 27 44 43 26 44 23 49", "30", "36", "46", "29", "7 18 14 33 4 22 41 4", "28", "45", "41 49 49 49 47 43 25 49 47 17 41 47 44 41 47 10", "12", "23", "20", "24 3 29 24 10 12 49 4 41 6 9 6 37", "29 25 49 3 41 44 41 6", "14 7 29 49 23 14 43", "21", "44 33 7 42 7 37 18 43 23 4 4 41", "34", "7 9", "26", "10 18 49 20 7 15 43 25 25 24 11 44 20", "46 6 31 2 41", "41", "10", "18 18 47 44 44 41 18 46 44 46 18 44", "44", "38", "22", "47", "17", "22 28 23 44 44 41 17 41 10 18 41 44 22 41", "49 25 49 42"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, numMonsters(Arg0)); }
	void test_case_1() { string Arr0[] = {"1 2", "2"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(1, Arg1, numMonsters(Arg0)); }
	void test_case_2() { string Arr0[] = {"2", "3", "1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(2, Arg1, numMonsters(Arg0)); }
	void test_case_3() { string Arr0[] = {"1", "3 4", "2", "2"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(3, Arg1, numMonsters(Arg0)); }
	void test_case_4() { string Arr0[] = {"2 2", "3", "4 4 4", "5", "6", "7 7 7 7", "7"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 24; verify_case(4, Arg1, numMonsters(Arg0)); }
	void test_case_5() { string Arr0[] = {"2 3","5 7","2 4","5","6","4","7"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(5, Arg1, numMonsters(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
  MonsterFarm ___test; 
        ___test.run_test(1);
        } 
// END CUT HERE

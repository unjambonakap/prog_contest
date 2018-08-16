// BEGIN CUT HERE

// END CUT HERE
#line 5 "TrafficMonitor.cpp"

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

#define REPV(i, n) for (int i = (n) - 1; (int)i >= 0; --i)
#define FOR(i, a, b) for(int i = (int)(a); i <= (int)(b); ++i)
#define FORV(i, a, b) for(int i = (int)(a); i >= (int)(b); --i)

#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();++i)
#define FEV(i,t) for (typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();++i)

#define SZ(a) (int((a).size()))
#define two(x) (1 << (x))
#define twoll(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()
#define CLR(a) (a).clear()


#define pb push_back
#define PF push_front
#define ST first
#define ND second
#define MP(x,y) make_pair(x, y)

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef queue<int> qi;

template<class T> void checkmin(T &a, T b){if (b<a)a=b;}
template<class T> void checkmax(T &a, T b){if (b>a)a=b;}
template<class T> void out(T t[], int n){REP(i, n)cout<<t[i]<<" "; cout<<endl;}
template<class T> void out(vector<T> t, int n=-1){for (int i=0; i<(n==-1?t.size():n); ++i) cout<<t[i]<<" "; cout<<endl;}
inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:(n==1?0:ctz(n>>1)+1));}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int maxn=55;

int graph[maxn][maxn];
int n;
int depth[maxn];
int cnt[maxn];
int pick[maxn];
int parent[maxn];


int dfs(int a, int d){
    depth[a]=d;
    cnt[a]=0;
    REP(i, n) if (graph[a][i] && depth[i]==-1) dfs(i, d+1), ++cnt[a], parent[i]=a;
}


class TrafficMonitor {
	public:
	int getMin(vector <string> links) {
        n=links.size();
        REP(i, n) REP(j, n) graph[i][j]=links[i][j]=='Y';

        memset(depth, -1, sizeof(depth)); memset(cnt, 0, sizeof(cnt));
        memset(parent, -1, sizeof(parent));
        REP(i, n) if (depth[i]==-1) dfs(i, 0);


        memset(pick, 0, sizeof(pick));
        REPV(i, n+1) REP(j, n) if (depth[j]==i && !pick[j]){
            if (!cnt[j]){
                pick[j]=0;
                if (parent[j]!=-1) pick[parent[j]]=1;
            }else{
                REP(i, n) if (parent[i]==j && !pick[i]){pick[j]=1; break;}

            }

        }
        int res=0;
        REP(i, n) res+=pick[i];


        return res;
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {
"NN",
"NN"
}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(0, Arg1, getMin(Arg0)); }
	void test_case_1() { string Arr0[] = {
"NYNN",
"YNYN",
"NYNY",
"NNYN"
}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(1, Arg1, getMin(Arg0)); }
	void test_case_2() { string Arr0[] = {
"NNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
"NNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
"NNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNYNNNNNNN",
"NNNNNNNNNNNNNYNNYNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNN",
"NNNNNNNNNNNNNNYNNNNNYNNNNNNNYNNNNNNNNNNNNNNNNNNNNN",
"NNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
"NNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNN",
"YNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNN",
"NYNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNYNNNNN",
"NNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNYNN",
"NNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNYNNNNNNNNNN",
"NNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNYNNYNNNNNNNN",
"NNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNN",
"NNNYNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
"NNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
"NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYN",
"NNNYNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNNNYNNN",
"NNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNN",
"NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNN",
"NNNNNNNNYYNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
"NNNNYNNNNNNNNNNNNNNNNNNNNNNYNNNNYNNNNNYNNNNNNNNNNN",
"NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNYN",
"NNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNN",
"NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNY",
"NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNYNN",
"NNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNYNNNN",
"NNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
"NNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNYNNN",
"NNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
"NNNNNNNNNNYYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
"NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
"NNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNN",
"NNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
"NNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNN",
"NNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
"NNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNN",
"NNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNYNNNNNN",
"NNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
"NNNNNNNNNNNYNNNNNNNNYYNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
"NNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNNNY",
"NNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNN",
"NNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
"NNYNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
"NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNN",
"NNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
"NNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNYNNNNNNNNNN",
"NNNNNNNNNNNNNNNNYNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNN",
"NNNNNNNNNYNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNN",
"NNNNNNNNNNNNNNNYNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
"NNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNYNNNNNNNNNN"
}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 22; verify_case(2, Arg1, getMin(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  TrafficMonitor ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE

// BEGIN CUT HERE

// END CUT HERE
#line 5 "KindAndCruel.cpp"

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
typedef vector<string> vs;

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

int K, C;
string f;
int n;
const int maxn=51, maxt=maxn*maxn*maxn+2;
const int inf=1e6;
int mem[maxn][maxt];

int proc(int p, int t){
    if (p==n) return 0;
    if (t==maxt) return inf;
    int &r=mem[p][t];
    if (r!=-1) return r;
    r=inf;
    if (f[p]=='.' || (f[p]=='K' && t%K) || (f[p]=='C' && t%C==0)) checkmin(r, 1+proc(p, t+1));
    if (f[p+1]=='.' || (f[p+1]=='K' && t%K) || (f[p+1]=='C' && t%C==0)) checkmin(r, 1+proc(p+1, t+1));
    return r;

}

class KindAndCruel {
	public:
	int crossTheField(string field, int _K, int _C) {
        f=field;
        K=_K, C=_C;
        memset(mem, -1, sizeof(mem));
        n=f.length()-1;
        int res=proc(0, 1);
        return res==inf?-1:res;
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "..."; int Arg1 = 2; int Arg2 = 5; int Arg3 = 2; verify_case(0, Arg3, crossTheField(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arg0 = ".K.C."; int Arg1 = 3; int Arg2 = 4; int Arg3 = 5; verify_case(1, Arg3, crossTheField(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arg0 = ".CCCC."; int Arg1 = 3; int Arg2 = 5; int Arg3 = -1; verify_case(2, Arg3, crossTheField(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arg0 = ".CKKKKCKKKKC.KKKKCKKKKC.CKKKKCKKKKCKKKKCKKKKCKKKK."; int Arg1 = 5; int Arg2 = 5; int Arg3 = 60; verify_case(3, Arg3, crossTheField(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  KindAndCruel ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE

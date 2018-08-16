// BEGIN CUT HERE

// END CUT HERE
#line 5 "Refactoring.cpp"

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


vi fact;
int m;
map<pii,int> mem;



int go(int n, int p){
    if (p==m) return n==1;
    if (fact[p]>n) return n==1;
    if (mem.count(MP(n,p))) return mem[MP(n,p)];
    int &r=mem[MP(n,p)];
    r=go(n, p+1);
    if (n%fact[p]==0) r+=go(n/fact[p], p);
    return r;
    
}

class Refactoring {
	public:
	int refactor(int n) {

        fact.clear();
        for (int i=2; i*i<=n; ++i) if (n%i==0) fact.pb(i), fact.pb(n/i);;
        sort(ALL(fact));
        fact.resize(unique(ALL(fact))-fact.begin());
        mem.clear();
        m=fact.size();
        return go(n, 0);
    }
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 24; int Arg1 = 6; verify_case(0, Arg1, refactor(Arg0)); }
	void test_case_1() { int Arg0 = 9973; int Arg1 = 0; verify_case(1, Arg1, refactor(Arg0)); }
	void test_case_2() { int Arg0 = 9240; int Arg1 = 295; verify_case(2, Arg1, refactor(Arg0)); }
	void test_case_3() { int Arg0 = 1916006400; int Arg1 = 7389115; verify_case(3, Arg1, refactor(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
  Refactoring ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE

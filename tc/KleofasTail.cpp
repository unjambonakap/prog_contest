// BEGIN CUT HERE

// END CUT HERE
#line 5 "KleofasTail.cpp"

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


class KleofasTail {
	public:
	long long countGoodSequences(long long K, long long A, long long B) {
        ll res=0;
        ll a=2;
        if (K==0){
            if (A==0) ++res;
            K=1;
        }
        if (K&1){
            if (K>=A && K<=B) ++res;
            K*=2;
        }
        while(K<=B){
            ll u=max(K,A), v=min(K+a-1,B);
            if (u<=v) res+=v-u+1;
            K*=2; a*=2;
        }
		
        return res;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long long Arg0 = 3LL; long long Arg1 = 4LL; long long Arg2 = 8LL; long long Arg3 = 2LL; verify_case(0, Arg3, countGoodSequences(Arg0, Arg1, Arg2)); }
	void test_case_1() { long long Arg0 = 1LL; long long Arg1 = 23457LL; long long Arg2 = 123456LL; long long Arg3 = 100000LL; verify_case(1, Arg3, countGoodSequences(Arg0, Arg1, Arg2)); }
	void test_case_2() { long long Arg0 = 1234567890123456LL; long long Arg1 = 10LL; long long Arg2 = 1000000LL; long long Arg3 = 0LL; verify_case(2, Arg3, countGoodSequences(Arg0, Arg1, Arg2)); }
	void test_case_3() { long long Arg0 = 0LL; long long Arg1 = 0LL; long long Arg2 = 2LL; long long Arg3 = 3LL; verify_case(3, Arg3, countGoodSequences(Arg0, Arg1, Arg2)); }
	void test_case_4() { long long Arg0 = 2LL; long long Arg1 = 3LL; long long Arg2 = 3LL; long long Arg3 = 1LL; verify_case(4, Arg3, countGoodSequences(Arg0, Arg1, Arg2)); }
	void test_case_5() { long long Arg0 = 13LL; long long Arg1 = 12345LL; long long Arg2 = 67890123LL; long long Arg3 = 8387584LL; verify_case(5, Arg3, countGoodSequences(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
  KleofasTail ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE

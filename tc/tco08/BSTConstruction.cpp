// BEGIN CUT HERE

// END CUT HERE
#line 5 "BSTConstruction.cpp"

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

inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}



const int maxn=2500010;
int height[maxn+1], p[maxn];
map<int, int> proc;

class BSTConstruction {
	public:
	long long sumHeights(int n, int seed, int limit) {

		ll x=seed;
		REP(i, n){
			p[i]=i;
			x=(x * 295397169) % 1073741789;
			if ((x * 1000000) / 1073741789 < limit){
				x= (x * 295397169) % 1073741789;
				int j= (x * (i + 1)) / 1073741789;
				swap(p[i], p[j]);
			}
		}
		ll res=0;

		CLR(proc);
		proc.insert(MP(n, n));
		height[n]=0;

		map<int, int>::iterator ita;
		REP(i, n){

			ita=proc.lower_bound(p[i]);
			assert(ita!=proc.end());
			res+=height[p[i]]=height[ita->ND]+1;
			ita->ND=p[i];
			proc.insert(MP(p[i], p[i]));
		}
		return res;

	}

	// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 10; int Arg1 = 12345678; int Arg2 = 500000; long long Arg3 = 40LL; verify_case(0, Arg3, sumHeights(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 10; int Arg1 = 87654321; int Arg2 = 1000000; long long Arg3 = 31LL; verify_case(1, Arg3, sumHeights(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 10; int Arg1 = 45454545; int Arg2 = 0; long long Arg3 = 55LL; verify_case(2, Arg3, sumHeights(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 1; int Arg1 = 99988877; int Arg2 = 12345; long long Arg3 = 1LL; verify_case(3, Arg3, sumHeights(Arg0, Arg1, Arg2)); }

	// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	BSTConstruction ___test; 
	___test.run_test(-1); 
} 
// END CUT HERE

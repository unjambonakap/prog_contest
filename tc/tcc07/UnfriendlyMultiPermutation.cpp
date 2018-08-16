// BEGIN CUT HERE

// END CUT HERE
#line 5 "UnfriendlyMultiPermutation.cpp"

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
inline int ctz(int n){return (n==0?-1:(n==1?0:ctz(n>>1)+1));}


const int mod=1e9+7;
const int maxn=20, maxk=5;

map<vi, int> state;
int tb[maxk+1];
int n, k;
vi end;

void rec(int p, int rem){
	if (p==k){
		REP(j, (rem==0?1:k)){
			tb[k]=j;
			state.insert(MP(vi(tb, tb+k+1), -1));
		}
	} else{
		REP(i, rem+1){
			tb[p]=i;
			rec(p+1, rem-i);
		}
	}
}
int proc(vi a){

	if (a==end)return 1;

	map<vi, int>::iterator itm=state.find(a);
	assert(itm!=state.end());
	int &r=itm->ND;
	if (r!=-1)return r;

	r=0;
	vi ns=a;
	if (a[k]>0) ++ns[a[k]-1];
	REP(i, k) if (ns[i]>0){
		int mul=ns[i]-(i==a[k]-1?1:0);
		
		--ns[i];
		ns[k]=i;
		ll t=proc(ns);
		if (t!=-1)r=(r+t*mul)%mod;
		++ns[i];
	}
	
	//REP(i, k+1) printf("%d ", a[i]); printf("=>> %d\n", r);


	return r;

}

class UnfriendlyMultiPermutation {
	public:
	int count(int _n, int _k) {
		n=_n, k=_k;
		end=vi(k+1, 0);

		CLR(state);

		rec(0, n);

		vi st(k+1, 0);
		st[k-1]=n;
		return proc(st);
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 2; int Arg2 = 2; verify_case(0, Arg2, count(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 3; int Arg1 = 2; int Arg2 = 30; verify_case(1, Arg2, count(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 5; int Arg1 = 1; int Arg2 = 120; verify_case(2, Arg2, count(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 2; int Arg1 = 4; int Arg2 = 2; verify_case(3, Arg2, count(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  UnfriendlyMultiPermutation ___test; 
        ___test.run_test(-1);
        } 
// END CUT HERE

// BEGIN CUT HERE

// END CUT HERE
#line 5 "PerfectPowers.cpp"

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



#define REP(i,n) for(i = 0; i < (n); i++)

#define REPV(i, n) for (i = (n) - 1; i >= 0; i--)
#define FOR(i, a, b) for(i = (a); i <= (b); i++)
#define FORV(i, a, b) for(i = (a); i >= (b); i--)

#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();i++)
#define FEV(i,t) for (typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();i++)

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


ll A, B, R;

void update(ll a, ll b){
	if (a>b)swap(a, b);
	if (a<A || b>B || a==b)return;
	if (R==-1 || b-a<R)R=b-a;
}

ll _sqrt(ll q){
	ll H, M, L, T;
	H=ceil(sqrt(double(q)))+1;
	L=0;
	while(H>L+1){
		M=(H+L)/2;
		if (M*M>q)H=M;
		else L=M;
	}
	assert(L*L<=q);
	assert(L*L+2*L+1>q);
	return L;
}


class PerfectPowers {
	public:
	long long nearestCouple(long long _A, long long _B) {
		A=_A, B=_B;

		vector<ll> pl; 
		ll i, j;
		int k;
		for (i=2; i*i*i<=B; ++i){
			j=i*i;

			while(j<=B/i)
				j*=i, pl.pb(j);
		}
		printf("%d\n", pl.size());
		sort(ALL(pl));
		R=-1;
		ll d;
		for (k=0; k<pl.size(); ++k)
			if (k==0 || pl[k]!=pl[k-1]){
				d=_sqrt(pl[k]);
				update((d-1)*(d-1), pl[k]);
				update(d*d, pl[k]);
				update((d+1)*(d+1), pl[k]);


				if (k>0)
					update(pl[k-1], pl[k]);
			}
		d=_sqrt(A);
		update(d*d, d*d+2*d+1);
		update(d*d+2*d+1, (d+2)*(d+2));
		return R;

	}

	// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long long Arg0 = 1LL; long long Arg1 = 4LL; long long Arg2 = 3LL; verify_case(0, Arg2, nearestCouple(Arg0, Arg1)); }
	void test_case_1() { long long Arg0 = 8LL; long long Arg1 = 9LL; long long Arg2 = 1LL; verify_case(1, Arg2, nearestCouple(Arg0, Arg1)); }
	void test_case_2() { long long Arg0 = 10LL; long long Arg1 = 15LL; long long Arg2 = -1LL; verify_case(2, Arg2, nearestCouple(Arg0, Arg1)); }
	void test_case_3() { long long Arg0 = 1LL; long long Arg1 = 1000000000000000000LL; long long Arg2 = 1LL; verify_case(3, Arg2, nearestCouple(Arg0, Arg1)); }
	void test_case_4() { long long Arg0 = 80000LL; long long Arg1 = 90000LL; long long Arg2 = 80LL; verify_case(4, Arg2, nearestCouple(Arg0, Arg1)); }

	// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	PerfectPowers ___test; 
	___test.run_test(-1); 
} 
// END CUT HERE

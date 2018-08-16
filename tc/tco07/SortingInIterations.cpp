// BEGIN CUT HERE

// END CUT HERE
#line 5 "SortingInIterations.cpp"

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


const int maxn=4*1e5+10;
int tb[maxn];

struct node{
	int st, nd, m;
	int ma, cnt;
	node *l, *r;
	node(int st, int nd):st(st), nd(nd){
		cnt=nd-st;
		if (st==nd-1){l=r=0; ma=tb[st];}
		else{
		   	m=(st+nd)/2;
			l=new node(st, m);
			r=new node(m, nd);
			ma=min(l->ma, r->ma);
		}
	}
	~node(){
		if (l!=0) delete l;
		if (r!=0) delete r;

	}
	ll rnd(int mx){
		if (ma>mx) return 0;
		if (cnt==0)return 0;
		if (l==0){
			--cnt; ma=INT_MAX;
			return tb[st];
		}
		int nm=min(mx, r->ma);
		ll a=0;
		if (l->ma<=nm) a+=l->rnd(nm);
		nm=min(mx, l->ma);
		if (r->ma<=nm) a+=r->rnd(nm);

		ma=min(l->ma, r->ma);
		cnt=l->cnt+r->cnt;
		return a;
	}


};

class SortingInIterations {
	public:
	long long sum(int a0, int X, int Y, int M, int n, int start, int finish) {
		tb[0]=a0;
		REP(i, n-1) tb[i+1]=(ll(tb[i])*X+Y)%M;
		node r(0, n);

		REP(i, start-1) r.rnd(INT_MAX);
		ll res=0;
		FOR(i, start, finish){
			if (r.cnt==0)return -1;
			res+=r.rnd(INT_MAX);
		}
		return res;


		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 1; int Arg2 = 400000; int Arg3 = 3; int Arg4 = 3; int Arg5 = 1; int Arg6 = 3; long long Arg7 = -1LL; verify_case(0, Arg7, sum(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	//void test_case_0() { int Arg0 = 4; int Arg1 = 2; int Arg2 = 0; int Arg3 = 7; int Arg4 = 10; int Arg5 = 1; int Arg6 = 1; long long Arg7 = 5LL; verify_case(0, Arg7, sum(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_1() { int Arg0 = 1; int Arg1 = 0; int Arg2 = 0; int Arg3 = 5; int Arg4 = 5; int Arg5 = 1; int Arg6 = 2; long long Arg7 = 1LL; verify_case(1, Arg7, sum(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_2() { int Arg0 = 7; int Arg1 = 6; int Arg2 = 9; int Arg3 = 10; int Arg4 = 10; int Arg5 = 2; int Arg6 = 3; long long Arg7 = 20LL; verify_case(2, Arg7, sum(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_3() { int Arg0 = 0; int Arg1 = 1; int Arg2 = 1; int Arg3 = 100000; int Arg4 = 100000; int Arg5 = 1; int Arg6 = 1; long long Arg7 = 4999950000LL; verify_case(3, Arg7, sum(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_4() { int Arg0 = 1; int Arg1 = 7; int Arg2 = 0; int Arg3 = 10; int Arg4 = 10; int Arg5 = 1; int Arg6 = 10; long long Arg7 = -1LL; verify_case(4, Arg7, sum(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  SortingInIterations ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE

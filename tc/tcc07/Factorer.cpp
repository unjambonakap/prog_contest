// BEGIN CUT HERE

// END CUT HERE
#line 5 "Factorer.cpp"

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


ll ca, cb, cc, cd;
bool fd=false;
int solve(ll a, ll b, ll c, ll &r, ll &rb){
	ll d=b*b-4*a*c;
	ll t=sqrt(d);
	if (t*t!=d)return 0;
	int res=0;
	if ((-b-t)%(2*a)==0)r=(-b-t)/(2*a), res|=1;
	if ((-b+t)%(2*a)==0)rb=(-b+t)/(2*a), res|=2;
	return res;
}

void updateSol(int a, int b, int c, int d){ if (!fd || a>ca || (a==ca && b>cb))ca=a, cb=b, cc=c, cd=d, fd=1; }
class Factorer {
	public:
	string factor(int a, int b, int c) {
		vi fa;
		fd=0;

		FOR(i, 1, floor(sqrt(fabs(a)))) if (a%i==0) fa.pb(i);
		FE(it, fa){
			ll na, nb, nc, nd, ndb;
			na=*it; nc=a/na;
			int r;
			if (r=solve(na, -b, ll(nc)*c, nd, ndb)){
				if (r&1) updateSol(na, c/nd, nc, nd);
				if (r&2) updateSol(na, c/ndb, nc, ndb);
			}
		}

		FE(it, fa){
			ll na, nb, nc, nd, ndb;
			nc=*it, na=a/nc;
			int r;
			if (r=solve(na, -b, ll(nc)*c, nd, ndb)){
				if (r&1) updateSol(na, c/nd, nc, nd);
				if (r&2) updateSol(na, c/ndb, nc, ndb);
			}
		}FE(it, fa){
			ll na, nb, nc, nd, ndb;
			na=-*it; nc=a/na;
			int r;
			if (r=solve(na, -b, ll(nc)*c, nd, ndb)){
				if (r&1) updateSol(na, c/nd, nc, nd);
				if (r&2) updateSol(na, c/ndb, nc, ndb);
			}
		}FE(it, fa){
			ll na, nb, nc, nd, ndb;
			nc=-*it, na=a/nc;
			int r;
			if (r=solve(na, -b, ll(nc)*c, nd, ndb)){
				if (r&1) updateSol(na, c/nd, nc, nd);
				if (r&2) updateSol(na, c/ndb, nc, ndb);
			}
		}

end:;
		
		if(!fd)return "NONE";
		return "("+(ca>1?toStr(ca):"")+"x"+(cb>=0?"+":"")+toStr(cb)+")("+(cc<0?"-":"")+(fabs(cc)>1?toStr(fabs(cc)):"")+"x"+(cd>=0?"+":"")+toStr(cd)+")";
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1000000; int Arg1 = 0; int Arg2 = -1000000; string Arg3 = "(x+1)(x-1)"; verify_case(0, Arg3, factor(Arg0, Arg1, Arg2)); }
	//void test_case_0() { int Arg0 = 1; int Arg1 = 0; int Arg2 = -1; string Arg3 = "(x+1)(x-1)"; verify_case(0, Arg3, factor(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = -4; int Arg1 = 4; int Arg2 = -1; string Arg3 = "(2x-1)(-2x+1)"; verify_case(1, Arg3, factor(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = -4; int Arg1 = 4; int Arg2 = 5; string Arg3 = "NONE"; verify_case(2, Arg3, factor(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 1; int Arg1 = -3; int Arg2 = 2; string Arg3 = "(x-1)(x-2)"; verify_case(3, Arg3, factor(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = -20; int Arg1 = 0; int Arg2 = 20; string Arg3 = "(20x+20)(-x+1)"; verify_case(4, Arg3, factor(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  Factorer ___test; 
        ___test.run_test(0);
        } 
// END CUT HERE

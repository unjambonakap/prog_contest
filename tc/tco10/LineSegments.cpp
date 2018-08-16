// BEGIN CUT HERE

// END CUT HERE
#line 5 "LineSegments.cpp"

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

const double pi=acos(-1.);

vi x, y;

double angle(int xa, int ya, int xb, int yb){
	double v=atan2(yb-ya, xb-xa);
	if (v<0) v+=2*pi;
	return v;
}

double modpi(double v){ return v+(v<0?2*pi:0); }

class LineSegments {
	public:
	long long intersections(int n, int xFirst, int xAdd, int xProd, int xMod, int yFirst, int yAdd, int yProd, int yMod) {
		if (n<4)return 0;
		int xo=xFirst;
		int yo=yFirst;
		x.clear(); y.clear();
		x.pb(xo); y.pb(yo);
		REP(i, n){
			xo=(ll(xo)*xProd+xAdd)%xMod;
			yo=(ll(yo)*yProd+yAdd)%yMod;
			x.pb(xo); y.pb(yo);
		}
		ll res=ll(n)*(n-1)*ll(n-2)*(n-3)/(2*3*4);
		REP(i, n){
			vector<double> ang;
			REP(j, n) if (i!=j) ang.pb(angle(x[i], y[i], x[j], y[j]));
			sort(ALL(ang));
			ll tmp=ll(n-1)*ll(n-2)*(n-3)/(3*2);
			int pos=0;
			REP(j, n-1){
				while(pos<j+n-1 && modpi(ang[pos%(n-1)]-ang[j])<pi) ++pos;
				tmp-=(ll(pos-j-1)*(pos-j-2))/2;
			}
			res-=tmp;
		}
		return res;

		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	//void test_case_0() { int Arg0 = 4; int Arg1 = 4; int Arg2 = 3; int Arg3 = 1; int Arg4 = 5; int Arg5 = 1; int Arg6 = 1; int Arg7 = 1; int Arg8 = 3; long long Arg9 = 0LL; verify_case(0, Arg9, intersections(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)); }
	void test_case_0() { int Arg0 = 526; int Arg1 = 3015; int Arg2 = 533; int Arg3 = 16915; int Arg4 = 27792; int Arg5 = 188904; int Arg6 = 653638; int Arg7 = 628948; int Arg8 = 740958; long long Arg9 = 0LL; verify_case(0, Arg9, intersections(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)); }
	void test_case_1() { int Arg0 = 4; int Arg1 = 1; int Arg2 = 2; int Arg3 = 1; int Arg4 = 3; int Arg5 = 1; int Arg6 = 1; int Arg7 = 1; int Arg8 = 2; long long Arg9 = 1LL; verify_case(1, Arg9, intersections(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)); }
	void test_case_2() { int Arg0 = 5; int Arg1 = 1; int Arg2 = 1; int Arg3 = 1; int Arg4 = 3; int Arg5 = 4; int Arg6 = 3; int Arg7 = 2; int Arg8 = 5; long long Arg9 = 3LL; verify_case(2, Arg9, intersections(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)); }
	void test_case_3() { int Arg0 = 6; int Arg1 = 1; int Arg2 = 3; int Arg3 = 1; int Arg4 = 5; int Arg5 = 1; int Arg6 = 2; int Arg7 = 1; int Arg8 = 3; long long Arg9 = 11LL; verify_case(3, Arg9, intersections(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)); }
	void test_case_4() { int Arg0 = 6; int Arg1 = 215657; int Arg2 = 553897; int Arg3 = 915611; int Arg4 = 930784; int Arg5 = 193666; int Arg6 = 323425; int Arg7 = 130393; int Arg8 = 654599; long long Arg9 = 15LL; verify_case(4, Arg9, intersections(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  LineSegments ___test; 
        ___test.run_test(-1);
        } 
// END CUT HERE

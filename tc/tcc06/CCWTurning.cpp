// BEGIN CUT HERE

// END CUT HERE
#line 5 "CCWTurning.cpp"

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


const double inf=1e10;
const double eps=1e-10;
const double pi=acos(-1.);


vi tb;
int n;
int r;


double dist(double x, double y){return sqrt(x*x+y*y);}
double norm(double ang){
    if (ang<0.) ang+=2*pi;
    if (ang>=2*pi) ang-=2*pi;
    return ang;
}
int checkit(double ang){
    ang=norm(ang);
    return ang>eps&&ang+eps<pi;
}


double proc(int p, double a, double b){
    a=norm(a); b=norm(b);
    if (p==n){return dist(r*cos(a)-r, r*sin(a));}
    if (tb[p]>2*r) return inf;
    double ang=acos(double(tb[p])/(2*r));
    double ans=inf;

    if (checkit(a+ang-pi-b)) checkmin(ans, proc(p+1, a-pi+2*ang, a-pi+ang));
    if (checkit(a+pi-ang-b)) checkmin(ans, proc(p+1, a+pi-2*ang, a+pi-ang));
    return ans;
}

class CCWTurning {
	public:
	double minDistance(int radius, vector <int> segLength) {
        tb=segLength; n=tb.size(); r=radius;
        double res=proc(0, 0., pi/2);
        return res>=inf?-1.:res;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 499; int Arr1[] = {498, 499, 499, 499, 499, 499, 499, 499, 499, 499, 499, 499, 499, 499, 499, 499, 499, 499, 499, 499, 499, 499, 499, 499, 499, 498}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = -1.0; verify_case(0, Arg2, minDistance(Arg0, Arg1)); }
	//void test_case_0() { int Arg0 = 499; int Arr1[] = {998, 499, 499, 499, 499, 499, 499, 499, 499, 499, 499, 499, 499, 499, 499, 499, 499, 499, 499, 499, 499, 499, 499, 499, 499, 998}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = -1.0; verify_case(0, Arg2, minDistance(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 5; int Arr1[] = {10,8}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 6.0; verify_case(1, Arg2, minDistance(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 5; int Arr1[] = {1,8} ; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 7.35989949685296; verify_case(2, Arg2, minDistance(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  CCWTurning ___test; 
        ___test.run_test(0); 
        } 
// END CUT HERE

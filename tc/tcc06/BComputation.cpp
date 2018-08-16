// BEGIN CUT HERE

// END CUT HERE
#line 5 "BComputation.cpp"

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
string toStr(ll a){ostringstream os; os<<a; return os.str();}


ll gcd(ll a, ll b){return b==0?a:gcd(b, a%b);}
struct frac{
    ll a, b;
    frac(){}
    frac(int x){a=x; b=1;}
    frac(ll a, ll b):a(a), b(b){}
    frac operator+(const frac &x)const{frac res(a*x.b+x.a*b, x.b*b); res.reduce(); return res;}
    frac operator-(const frac &x)const{frac res(a*x.b-x.a*b, x.b*b); res.reduce(); return res;}
    frac operator/(ll x)const{ frac res=*this; res.b*=x; res.reduce(); return res; }
    frac operator*(ll x)const{ frac res=*this; res.a*=x; res.reduce(); return res; }
    void reduce(){ll d=gcd(max(a, b), min(a, b)); a/=d; b/=d;}
    string disp()const{int sgn=b<0?-1:1; return toStr(a*sgn)+"/"+toStr(b*sgn);}
};

const int maxn=17;
ll fact[maxn];
ll cnk(int n, int k){return fact[n]/fact[k]/fact[n-k];}

class BComputation {
	public:
	string getValue(int bo, int pos) {
        fact[0]=1;
        REP(i, pos+2) if (i) fact[i]=fact[i-1]*i;

        frac tb[pos+1];
        tb[0]=frac(bo);
        FOR(i, 1, pos){
            frac tmp(0);
            REP(j, i) tmp=tmp-tb[j]*cnk(i+1, j);
            tb[i]=tmp/(i+1);

        }
        return tb[pos].disp();
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 0; string Arg2 = "1/1"; verify_case(0, Arg2, getValue(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 1; int Arg1 = 1; string Arg2 = "-1/2"; verify_case(1, Arg2, getValue(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 100; int Arg1 = 11; string Arg2 = "0/1"; verify_case(2, Arg2, getValue(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 92; int Arg1 = 12; string Arg2 = "-31786/1365"; verify_case(3, Arg2, getValue(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  BComputation ___test; 
        ___test.run_test(-1);
        } 
// END CUT HERE

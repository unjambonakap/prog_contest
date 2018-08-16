// BEGIN CUT HERE

// END CUT HERE
#line 5 "Synchro.cpp"

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

ll _gcd(ll a, ll b){return (!b?a:_gcd(b, a%b));}
ll gcd(ll a, ll b){
    if (a<b) swap(a, b);
    return _gcd(a, b);
}

struct frac{
    frac(int _a, int _b){
        int d=gcd(_a, _b);
        a=_a/d, b=_b/d;
    }
    frac(){}
    int a, b;
};

const int maxn=55;
frac tb[maxn];

class Synchro {
	public:
	double resynch(vector <int> watch) {
        sort(ALL(watch));
        vi::iterator ita=unique(ALL(watch));
        watch.resize(ita-watch.begin());

        int x=watch.back();
        watch.pop_back();
        int n=watch.size();
        if (n==0) return 0.;


        REP(i, n) tb[i]=frac(60, x-watch[i]);
        ll res[maxn];
        REP(i, n){
            res[i]=tb[i].b;
            REP(j, n) if (j!=i) res[i]*=tb[j].a;
        }
        ll d=res[n-1];
        REP(i, n-1) d=gcd(d, res[i]);
        double tmp=double(tb[0].a*res[0]/d)/tb[0].b;
        tmp*=watch[0];

        return tmp-floor(tmp/60)*60;;
        



		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {59,59,59}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 0.0; verify_case(0, Arg1, resynch(Arg0)); }
	void test_case_1() { int Arr0[] = {60,53}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 34.28571428571427; verify_case(1, Arg1, resynch(Arg0)); }
	void test_case_2() { int Arr0[] = {120,40}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 30.0; verify_case(2, Arg1, resynch(Arg0)); }
	void test_case_3() { int Arr0[] = {1, 2, 4, 8, 16, 32, 64, 128}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 0.0; verify_case(3, Arg1, resynch(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  Synchro ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE

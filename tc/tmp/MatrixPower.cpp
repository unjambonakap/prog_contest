// BEGIN CUT HERE

// END CUT HERE
#line 5 "MatrixPower.cpp"

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

const int mod=1e9+7;
const int maxn=11111;
int n;
ll A, B, C;
ll qx[maxn];

struct matrix{
    ll a, b, c, d;
    matrix(){a=b=c=d=0;}
    matrix operator*(const matrix &m)const{
        matrix r;
        ll b1=a, b2=b, b3=c, b4=d;
        ll c1=m.a, c2=m.b, c3=m.c, c4=m.d;
        r.a=n*b1%mod*c1+b1*c2%mod*A+b3*c1%mod*B+b3*c2%mod*C; r.a%=mod;
        r.b=n*b2%mod*c1+b2*c2%mod*A+b4*c1%mod*B+b4*c2%mod*C; r.b%=mod;
        r.c=n*b1%mod*c3+b1*c4%mod*A+b3*c3%mod*B+b3*c4%mod*C; r.c%=mod;
        r.d=n*b2%mod*c3+b2*c4%mod*A+b4*c3%mod*B+b4*c4%mod*C; r.d%=mod;
        return r;
    }

};

matrix fexp(matrix a, int p){
    matrix x=a;
    for (--p; p; p>>=1, a=a*a) if (p&1) x=x*a;
    return x;
}

class MatrixPower {
	public:
	vector <int> getElements(int d, int q, int _n, int k, vector <int> rows, vector <int> columns) {
        n=_n;
        A=B=C=0;
        qx[0]=1;
        REP(i, n) A+=i, B+=qx[i], C+=i*qx[i], qx[i+1]=qx[i]*q%mod;
        A%=mod; B%=mod; C%=mod;
        matrix x;
        x.a=x.d=0;
        x.b=d; x.c=1;
        x=fexp(x, k);
        vi res;
        REP(i, rows.size()) res.pb((x.a+x.b*rows[i]+x.c*qx[columns[i]]+x.d*qx[columns[i]]%mod*rows[i]%mod)%mod);
        return res;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 2; int Arg2 = 2; int Arg3 = 2; int Arr4[] = {0,0,1,1}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {0,1,0,1}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arr6[] = {5, 8, 8, 13 }; vector <int> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); verify_case(0, Arg6, getElements(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_1() { int Arg0 = 0; int Arg1 = 1; int Arg2 = 10; int Arg3 = 3; int Arr4[] = {0,1,2,3,4,5,6,7,8,9}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {0,1,2,3,4,5,6,7,8,9}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arr6[] = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100 }; vector <int> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); verify_case(1, Arg6, getElements(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_2() { int Arg0 = 0; int Arg1 = 1000000000; int Arg2 = 1; int Arg3 = 1000000000; int Arr4[] = {0,0,0}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {0,0,0}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arr6[] = {1, 1, 1 }; vector <int> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); verify_case(2, Arg6, getElements(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_3() { int Arg0 = 1000000000; int Arg1 = 1000000000; int Arg2 = 100; int Arg3 = 1000000000; int Arr4[] = {0}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {0}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arr6[] = {380113608 }; vector <int> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); verify_case(3, Arg6, getElements(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
  MatrixPower ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE

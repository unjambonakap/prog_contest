// BEGIN CUT HERE

// END CUT HERE
#line 5 "CircularShifts.cpp"

#include<complex>
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

typedef complex<double> point;
typedef vector<point> vc;
const double pi=acos(-1.);

vc fft(const vc &a, point w){
    int n=a.size();
    if (n==1) return a;
    vc na[2];
    na[0].resize(n/2);
    na[1].resize(n/2);
    REP(i,n) na[i&1][i>>1]=a[i];
    na[0]=fft(na[0],w*w);
    na[1]=fft(na[1],w*w);
    vc res(n);
    point wp=point(1.,0);
    REP(i,n/2){
        point x=na[1][i]*wp;
        res[i]=na[0][i]+x;
        res[n/2+i]=na[0][i]-x;
        wp*=w;
    }
    return res;
}


vi go(vc a, vc b){
    int n=a.size();
    int bx=1;
    while(bx<n) bx<<=1;
    n=bx<<1;
    a.resize(n,0);
    b.resize(n,0);


    point w(cos(2*pi/n),sin(2*pi/n));
    vc x=fft(a,w);
    vc y=fft(b,w);


    REP(i,n) x[i]=x[i]*y[i];

    vc res=fft(x,conj(w));
    vi ans(n);
    REP(i,n) ans[i]=res[i].real()/n+0.1;
    return ans;
}

class CircularShifts {
	public:
	int maxScore(int N, int Z0, int A, int B, int M) {
        vi z(2*N);
        z[0]=Z0%M;
        FOR(i,1,2*N) z[i]=(1ll*z[i-1]*A+B)%M;
        vc x(2*N);
        vc y(2*N,0);
        REP(i,2*N) x[i]=point(z[i%N]%100,0);
        REP(i,N) y[i]=point(z[2*N-i-1]%100,0);

        vi res=go(x,y);
        int ans=0;
        FOR(i,N-1,2*N-1) checkmax(ans,res[i]);
        return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 36972; int Arg1 = 308338165; int Arg2 = 7727024; int Arg3 = 10609552; int Arg4 = 106827339; int Arg5 = 5; verify_case(0, Arg5, maxScore(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_1() { int Arg0 = 4; int Arg1 = 1; int Arg2 = 1; int Arg3 = 1; int Arg4 = 20; int Arg5 = 70; verify_case(1, Arg5, maxScore(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_2() { int Arg0 = 10; int Arg1 = 23; int Arg2 = 11; int Arg3 = 51; int Arg4 = 4322; int Arg5 = 28886; verify_case(2, Arg5, maxScore(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_3() { int Arg0 = 1000; int Arg1 = 3252; int Arg2 = 3458736; int Arg3 = 233421; int Arg4 = 111111111; int Arg5 = 2585408; verify_case(3, Arg5, maxScore(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_4() { int Arg0 = 141; int Arg1 = 96478; int Arg2 = 24834; int Arg3 = 74860; int Arg4 = 92112; int Arg5 = 419992; verify_case(4, Arg5, maxScore(Arg0, Arg1, Arg2, Arg3, Arg4)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
  CircularShifts ___test; 
        ___test.run_test(0);
        } 
// END CUT HERE

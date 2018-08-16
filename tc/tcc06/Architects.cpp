// BEGIN CUT HERE

// END CUT HERE
#line 5 "Architects.cpp"

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


typedef long double ld;
ld k;
ld ba;
int n, K;


int checkit(ld a){
    ld s=0;
    REP(i, n-1){
        s+=a*10;
        ld va=s/(i==n-2?K+10:K), vb=max((ld)0., sqrt(a)-k);
        vb*=vb;
        a=max(va, vb);
    }
    return a<=ba;

}

class Architects {
	public:
	ld roofArea(int w, int l, int _n, int _K) {
        n=_n; K=_K;
        if (n==1) return w*l;
        if (K<10) return -1.;
        if (K==10) return n==2?w*l:-1.;



        K-=10;
        ba=w*l;
        k=ld(w)/l;
        k=100*sqrt(k/(1+k*k));


        ld T=0., H=1e11;
        REP(step, 1000){
            ld M=(T+H)/2.;
            if (checkit(M)) T=M;
            else H=M;
        }
        return T;
        




		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const ld &Expected, const ld &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	//void test_case_0() { int Arg0 = 1000; int Arg1 = 1000; int Arg2 = 2; int Arg3 = 5; ld Arg4 = -1.0; verify_case(0, Arg4, roofArea(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_0() { int Arg0 = 4999; int Arg1 = 3; int Arg2 = 10; int Arg3 = 75; ld Arg4 = -1.0; verify_case(0, Arg4, roofArea(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 1000; int Arg1 = 1000; int Arg2 = 1; int Arg3 = 5; ld Arg4 = 1000000.0; verify_case(1, Arg4, roofArea(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 6; int Arg1 = 8; int Arg2 = 2; int Arg3 = 3000; ld Arg4 = 5808.0; verify_case(2, Arg4, roofArea(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 100; int Arg1 = 200; int Arg2 = 3; int Arg3 = 40; ld Arg4 = 52489.99599679679; verify_case(3, Arg4, roofArea(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  Architects ___test; 
        ___test.run_test(0);
        } 
// END CUT HERE

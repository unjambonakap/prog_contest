// BEGIN CUT HERE

// END CUT HERE
#line 5 "AlienMultiplication.cpp"

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

int A[6], B[6], C[6];
int rema[7], remb[7], remc[7];
int px[7];
int best;
void go(int p, int x, int a, int b, int c){
    if (p==6){checkmin(best, x); return;}
    if (x>best) return;
    REP(i, 10) REP(j, 10) REP(k, 10){
        int nx=x+(i!=A[p])+(j!=B[p])+(k!=C[p]);
        if (nx>best) continue;
        int na=a+i*px[p], nb=b+j*px[p], nc=c+k*px[p];
        if (1LL*na*nb%px[p+1]==nc) go(p+1, nx, na, nb, nc);
    }
    
}

class AlienMultiplication {
	public:
	int getCorrections(int a, int b, int c) {
        px[0]=1;
        REP(i, 6) px[i+1]=px[i]*10;
        rema[6]=remb[6]=remc[6]=0;
        REP(i, 6) A[i]=a%10, rema[i]=a*px[i], a/=10;
        REP(i, 6) B[i]=b%10, remb[i]=b*px[i], b/=10;
        REP(i, 6) C[i]=c%10, remc[i]=c*px[i], c/=10;
        best=6;
        go(0, 0, 0,0,0);
        return best;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 23; int Arg1 = 11; int Arg2 = 2093; int Arg3 = 1; verify_case(0, Arg3, getCorrections(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 1538; int Arg1 = 951234; int Arg2 = 997892; int Arg3 = 0; verify_case(1, Arg3, getCorrections(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 153; int Arg1 = 7; int Arg2 = 71; int Arg3 = 1; verify_case(2, Arg3, getCorrections(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 421368; int Arg1 = 512357; int Arg2 = 862812; int Arg3 = 4; verify_case(3, Arg3, getCorrections(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 0; int Arg1 = 0; int Arg2 = 987654; int Arg3 = 5; verify_case(4, Arg3, getCorrections(Arg0, Arg1, Arg2)); }
	void test_case_5() { int Arg0 = 999999; int Arg1 = 999999; int Arg2 = 1; int Arg3 = 0; verify_case(5, Arg3, getCorrections(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
  AlienMultiplication ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE

// BEGIN CUT HERE

// END CUT HERE
#line 5 "SquareFree.cpp"

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

const int maxn=1e5;
int isp[maxn];
int pl[maxn];
int np;

int go(int n, int p, int sgn){
    if (p==np || n<pl[p]) return sgn*n;
    return go(n, p+1, sgn)+go(n/pl[p], p+1, sgn*-1);
}


int hasSquare(int n){
    REP(i, np){
        if (pl[i]>n) break;
        if (n%pl[i]==0) return 1;
    }
    return 0;
}

class SquareFree {
	public:
	int getNumber(int n) {
        np=0;
        memset(isp, 1, sizeof(isp));
        FOR(i, 2, maxn) if (isp[i] && 1LL*i*i<INT_MAX){
            for (ll j=i*i; j<maxn; j+=i) isp[j]=0;
            pl[np++]=i*i;
        }


        ll H=INT_MAX, T=n;
        while(T+1<H){
            int M=(T+H)/2;
            int x=go(M,0,1);
            if (x>n || (x==n && hasSquare(M))) H=M;
            else T=M;
        }
        return T;
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 1; verify_case(0, Arg1, getNumber(Arg0)); }
	void test_case_1() { int Arg0 = 13; int Arg1 = 19; verify_case(1, Arg1, getNumber(Arg0)); }
	void test_case_2() { int Arg0 = 100; int Arg1 = 163; verify_case(2, Arg1, getNumber(Arg0)); }
	void test_case_3() { int Arg0 = 1234567; int Arg1 = 2030745; verify_case(3, Arg1, getNumber(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
  SquareFree ___test; 
        ___test.run_test(-1);
        } 
// END CUT HERE

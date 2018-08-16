// BEGIN CUT HERE

// END CUT HERE
#line 5 "RepeatedAddition.cpp"

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
ll toll(string s){ll a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}



class RepeatedAddition {
	public:
	long long digitsErased(string A, string B, string X) {

        ll a, b, x;
        a=toll(A); b=toll(B); x=toll(X);
        ll na=(b-a)/x;
        ll res=0;
        ll p=1;
        ll nc=0;
        ll fc=0;
        REP(i, B.length()){
            int u=x/p%10;
            ll tmp=0;
            if (u==9) tmp=na-nc;
            else if (u==0) tmp=nc;
            else tmp=na;
            if (i>=X.length() && i>=A.length()) --tmp;
            else if (i>=A.length()){
                if (u==0) tmp-=fc;
                else --tmp;
            }
            res+=max(0LL, tmp);
            fc=((a/p)%10+u+fc)/10;
            nc=((a/p)%10+u*na+nc)/10;
            p*=10;
        }

        return res;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "8"; string Arg1 = "211"; string Arg2 = "101"; long long Arg3 = 5LL; verify_case(0, Arg3, digitsErased(Arg0, Arg1, Arg2)); }
	//void test_case_0() { string Arg0 = "2"; string Arg1 = "6"; string Arg2 = "1"; long long Arg3 = 4LL; verify_case(0, Arg3, digitsErased(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arg0 = "88"; string Arg1 = "107"; string Arg2 = "19"; long long Arg3 = 2LL; verify_case(1, Arg3, digitsErased(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arg0 = "123"; string Arg1 = "843"; string Arg2 = "120"; long long Arg3 = 12LL; verify_case(2, Arg3, digitsErased(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arg0 = "3"; string Arg1 = "811"; string Arg2 = "404"; long long Arg3 = 4LL; verify_case(3, Arg3, digitsErased(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arg0 = "2043601634821768"; string Arg1 = "4274721675435952"; string Arg2 = "3653414"; long long Arg3 = 4522764117LL; verify_case(4, Arg3, digitsErased(Arg0, Arg1, Arg2)); }
	void test_case_5() { string Arg0 = "12"; string Arg1 = "123"; string Arg2 = "111"; long long Arg3 = 2LL; verify_case(5, Arg3, digitsErased(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  RepeatedAddition ___test; 
        ___test.run_test(-1);
        } 
// END CUT HERE

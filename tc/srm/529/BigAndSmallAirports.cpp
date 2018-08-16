// BEGIN CUT HERE

// END CUT HERE
#line 5 "BigAndSmallAirports.cpp"

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



ll gets(int v){ return 1ll*v*(v+1)/2; }

class BigAndSmallAirports {
	public:
	long long solve(int Nlo, int Nhi, int Blo, int Bhi, int Slo, int Shi) {
        ll res=0;

        FOR(i, Blo, Bhi+1) FOR(j, Slo, Shi+1) if (j<i){
            int ub=i+1;
            FOR(k, 1, min(ub, Nhi+1)){
                int bd=max(Nlo, (int)ceil(1.*k*(i+j+1-k)/j));
                checkmax(bd, i+1);
                res+=max(0, Nhi-bd+1);
            }
            
            if (ub<=Nhi){
                int st=max(Nlo, ub);
                res+=gets(Nhi-st+1)+1ll*(Nhi-st+1)*(st-ub);
            }
            

            if (j==1){
                if (1>=Nlo && 1<=Nhi) ++res;
                if (2>=Nlo && 2<=Nhi) ++res;
            }else res+=Nhi-Nlo+1;
        }
        return res;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	//void test_case_0() { int Arg0 = 20; int Arg1 = 20; int Arg2 = 3; int Arg3 = 3; int Arg4 = 2; int Arg5 = 2; long long Arg6 = 21LL; verify_case(0, Arg6, solve(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_0() { int Arg0 = 1234567; int Arg1 = 9876543; int Arg2 = 20; int Arg3 = 170; int Arg4 = 10; int Arg5 = 160; long long Arg6 = 21LL; verify_case(0, Arg6, solve(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_1() { int Arg0 = 1; int Arg1 = 1; int Arg2 = 10; int Arg3 = 10; int Arg4 = 2; int Arg5 = 2; long long Arg6 = 1LL; verify_case(1, Arg6, solve(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_2() { int Arg0 = 10; int Arg1 = 10; int Arg2 = 8; int Arg3 = 8; int Arg4 = 3; int Arg5 = 3; long long Arg6 = 6LL; verify_case(2, Arg6, solve(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_3() { int Arg0 = 10; int Arg1 = 100; int Arg2 = 13; int Arg3 = 15; int Arg4 = 18; int Arg5 = 22; long long Arg6 = 0LL; verify_case(3, Arg6, solve(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_4() { int Arg0 = 30; int Arg1 = 32; int Arg2 = 8; int Arg3 = 10; int Arg4 = 6; int Arg5 = 8; long long Arg6 = 768LL; verify_case(4, Arg6, solve(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
  BigAndSmallAirports ___test; 
        ___test.run_test(0); 
        } 
// END CUT HERE

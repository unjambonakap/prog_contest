// BEGIN CUT HERE

// END CUT HERE
#line 5 "InverseCollatz.cpp"

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


const int maxn=55;

ll prev(char c, ll v){
    if (c=='E') return 2*v;
    --v;
    if (v%3) return -1;
    v/=3;
    if (v%2==0) return -1;
    return v;
}



class InverseCollatz {
	public:
	string getForm(string s) {
        ll a=1, b=0;
        REPV(i, s.length()){
            ll va, vb;
            va=vb=-1;

            for (ll k=0;; ++k){
                ll t=prev(s[i], a*k+b);
                if (t!=-1){
                    if (va==-1) va=t;
                    else{ vb=t; break;}
                }
            }
            a=vb-va; b=va;
        }
        ostringstream os;
        os<<a<<"k+"<<b;
        return os.str();
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "EEE"; string Arg1 = "8k+0"; verify_case(0, Arg1, getForm(Arg0)); }
	void test_case_1() { string Arg0 = "OE"; string Arg1 = "2k+1"; verify_case(1, Arg1, getForm(Arg0)); }
	void test_case_2() { string Arg0 = "OEO"; string Arg1 = "4k+3"; verify_case(2, Arg1, getForm(Arg0)); }
	void test_case_3() { string Arg0 = "EEEEOEEEEOEEEEOEEEEOEEEEOEEEEOEEEEOEEEEOEEEEOEEEEO"; string Arg1 = "2199023255552k+1014933810256"; verify_case(3, Arg1, getForm(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  InverseCollatz ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE

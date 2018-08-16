// BEGIN CUT HERE

// END CUT HERE
#line 5 "TheBoringGameDivTwo.cpp"

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



class TheBoringGameDivTwo {
	public:
	vector <int> find(int sa, int ka, int sb, int kb, int sf, int kf) {
		int ma, mb; ma=INT_MAX, mb=INT_MIN;

		REP(wf, min(ka, kb)+1){
			int wa=kb-wf, wb=ka-wf;
			int wab=kf-wa-wb;
			if (wab<0)continue;
			REP(ak, wab+1) REP(tka_w, wa+1) REP(tkb_w, wb+1){
				int bk=wab-ak;
				int fkb_l=wa-tka_w;
				int fka_l=wb-tkb_w;
				int tka_l=ak+fkb_l-sa;
				int tkb_l=bk+fka_l-sb;
				int fk=ka-fka_l-tkb_l-tkb_w-tka_l;
				

				if (fkb_l<0 || fka_l<0 || tka_l<0 || tkb_l<0 || fk<0)continue;
				if (sa!=ak+fkb_l-tka_l || sb!=bk+fka_l-tkb_l || sf!=2*fk+fkb_l+fka_l+tka_l+tkb_l) continue;
				if (ka!=fk+tkb_l+tkb_w+fka_l+tka_l || kb!=fk+tka_l+tka_w+fkb_l+tkb_l || kf!=ak+bk+fka_l+fkb_l+tka_w+tkb_w)continue;
				checkmin(ma, wa+wb+wab+wf);
				checkmax(mb, wa+wb+wab+wf);

			}
			


		}
		
		vi res;
		if (ma<=mb) res.pb(ma), res.pb(mb);
		return res;

		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 1; int Arg2 = 1; int Arg3 = 1; int Arg4 = 2; int Arg5 = 2; int Arr6[] = {2, 3 }; vector <int> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); verify_case(0, Arg6, find(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_1() { int Arg0 = 0; int Arg1 = 0; int Arg2 = 0; int Arg3 = 0; int Arg4 = 0; int Arg5 = 0; int Arr6[] = {0, 0 }; vector <int> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); verify_case(1, Arg6, find(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_2() { int Arg0 = 4; int Arg1 = 7; int Arg2 = -2; int Arg3 = 5; int Arg4 = 1; int Arg5 = 9; int Arr6[] = { }; vector <int> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); verify_case(2, Arg6, find(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_3() { int Arg0 = 1; int Arg1 = 5; int Arg2 = -1; int Arg3 = 4; int Arg4 = 3; int Arg5 = 6; int Arr6[] = {8, 9 }; vector <int> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); verify_case(3, Arg6, find(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  TheBoringGameDivTwo ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE

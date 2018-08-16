// BEGIN CUT HERE

// END CUT HERE
#line 5 "OptimalGroupMovement.cpp"

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
int mp[maxn];
int n;
class OptimalGroupMovement {
	public:

	int minimumCost(string board) {
		n=board.size();
		REP(i, n) mp[i]=(board[i]=='X');
		vector<pii> grp;
		REP(i, n) if (mp[i]){
			if (i==0 || !mp[i-1])grp.pb(MP(i, 1));
			else ++grp.back().ND;
		}
		int res=INT_MAX;
		REP(i, grp.size()){
			int tmp=0;
			int p=grp[i].ST;
			REPV(j, i) tmp+=(p-grp[j].ST-grp[j].ND)*grp[j].ND*grp[j].ND, p-=grp[j].ND;
			p=grp[i].ST+grp[i].ND;
			FOR(j, i+1, grp.size()-1) tmp+=(grp[j].ST-p)*grp[j].ND*grp[j].ND, p+=grp[j].ND;
			checkmin(res, tmp);

		}
		return res;

		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = ".XXX.XXXX."; int Arg1 = 9; verify_case(0, Arg1, minimumCost(Arg0)); }
	void test_case_1() { string Arg0 = "X"; int Arg1 = 0; verify_case(1, Arg1, minimumCost(Arg0)); }
	void test_case_2() { string Arg0 = "XXXXX...X..X.X"; int Arg1 = 14; verify_case(2, Arg1, minimumCost(Arg0)); }
	void test_case_3() { string Arg0 = ".X.X.X..X.X.X.......XX..X.X..X"; int Arg1 = 70; verify_case(3, Arg1, minimumCost(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  OptimalGroupMovement ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE

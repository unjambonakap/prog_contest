// BEGIN CUT HERE

// END CUT HERE
#line 5 "BreakingChocolate.cpp"

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

const int maxn=47;
const int maxw=83;

int n;
map<int, int> remapx, remapy;
int w, h;
int cntp[maxw][maxw];
unsigned char dp[maxw][maxw][maxw][maxw];
vector<pii> pts;

inline int cnt_rect(int xa, int xb, int ya, int yb){ return cntp[xb+1][yb+1]-cntp[xa][yb+1]+cntp[xa][ya]-cntp[xb+1][ya]; }

unsigned char proc(int xa, int xb, int ya, int yb){
	int cnt=cnt_rect(xa, xb, ya, yb);
	if (cnt==0)return 0;
	unsigned char v=0;
	if (cnt_rect(xa, xa, ya, yb)==0){
		++v;
		while(cnt_rect(xa, xa, ya, yb)==0) ++xa;
	}
	if (cnt_rect(xb, xb, ya, yb)==0){
		while(cnt_rect(xb, xb, ya, yb)==0) --xb;
		++v;
	}
	if (cnt_rect(xa, xb, ya, ya)==0){
		while(cnt_rect(xa, xb, ya, ya)==0) ++ya; ++v; 
	}
	if (cnt_rect(xa, xb, yb, yb)==0){
		while(cnt_rect(xa, xb, yb, yb)==0) --yb; ++v;
	}

	unsigned char &r=dp[xa][xb][ya][yb];
	if (r!=255) return r+v;
	assert(xb+1<maxw);
	assert(yb+1<maxw);
	cnt=cnt_rect(xa, xb, ya, yb);
	int sz=(xb-xa+1)*(yb-ya+1);

	r=0;
	if (cnt==sz) return v; 
	r=200;
	int res=INT_MAX;
	unsigned char tmp;
	FOR(i, xa, xb-1) checkmin(res, (1+proc(xa, i, ya, yb)+proc(i+1, xb, ya, yb)));
	FOR(i, ya, yb-1) checkmin(res, (1+proc(xa, xb, ya, i)+proc(xa, xb, i+1, yb)));
	assert(res!=INT_MAX);

	r=res;
	return r+v;

}

class BreakingChocolate {
	public:
		int minSteps(int W, int H, vector <int> sx, vector <int> sy) {
			vi nsx, nsy; n=sx.size();
			FE(it, sx) --*it;
			FE(it, sy) --*it;
			nsx=sx; nsy=sy;



			sort(ALL(nsx)); sort(ALL(nsy));
			remapx.clear(); remapy.clear();
			int res=0;
			if (nsx[0]>0) ++res;
			REP(i, n) remapx[nsx[i]]=(i==0?0:remapx[nsx[i-1]]+(nsx[i-1]+1<nsx[i]?2:nsx[i]-nsx[i-1]));
			if (nsx[n-1]<W-1) ++res;

			if (nsy[0]>0) ++res;
			REP(i, n) remapy[nsy[i]]=(i==0?0:remapy[nsy[i-1]]+(nsy[i-1]+1<nsy[i]?2:nsy[i]-nsy[i-1]));
			if (nsy[n-1]<H-1) ++res;



			w=remapx[nsx[n-1]]; h=remapy[nsy[n-1]];

			pts.clear();
			REP(i, n) pts.pb(MP(remapx[sx[i]], remapy[sy[i]]));

			memset(cntp, 0, sizeof(cntp));
			REP(i, w+2) REP(j, h+2) FE(it, pts) if (it->ST<i && it->ND<j) ++cntp[i][j];


			//dp.clear();
			memset(dp, -1, sizeof(dp));
			return proc(0, w, 0, h)+res;
		}

		// BEGIN CUT HERE
	public:
		void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
		template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
		void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
		void test_case_0() { int Arg0 = 547; int Arg1 = 523; int Arr2[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250, 260, 270, 280, 290, 300, 310, 320, 330, 340, 350, 360, 370, 380, 390, 400}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250, 260, 270, 280, 290, 300, 310, 320, 330, 340, 350, 360, 370, 380, 390, 400}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 4; verify_case(0, Arg4, minSteps(Arg0, Arg1, Arg2, Arg3)); }
		void test_case_1() { int Arg0 = 2; int Arg1 = 2; int Arr2[] = {1,2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {2,1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 3; verify_case(1, Arg4, minSteps(Arg0, Arg1, Arg2, Arg3)); }
		void test_case_2() { int Arg0 = 10; int Arg1 = 10; int Arr2[] = {1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 2; verify_case(2, Arg4, minSteps(Arg0, Arg1, Arg2, Arg3)); }
		void test_case_3() { int Arg0 = 10; int Arg1 = 10; int Arr2[] = {3,5,6}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {5,5,5}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 6; verify_case(3, Arg4, minSteps(Arg0, Arg1, Arg2, Arg3)); }
		void test_case_4() { int Arg0 = 3; int Arg1 = 3; int Arr2[] = {1,1,1,2,2,3,3,3}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1,2,3,1,3,1,2,3}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 4; verify_case(4, Arg4, minSteps(Arg0, Arg1, Arg2, Arg3)); }

		// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	BreakingChocolate ___test; 
	___test.run_test(0);
} 
// END CUT HERE

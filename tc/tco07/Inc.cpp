// BEGIN CUT HERE

// END CUT HERE
#line 5 "Inc.cpp"

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

const int maxn=5;
const int maxe=3*3*3*3*3;
const int maxt=11;
vector<vi> board;
int n, m;

pii dp[maxe][maxe][maxt];
int gain[maxe][maxe][3];
int seen[maxe][maxe][maxt];
int nt, inc;
int tcol[maxn], trow[maxn];

inline int win(int r, int c, int p){
	int eq=2;
	REP(i, 3) if (i!=p){
	   	if (gain[r][c][i]>gain[r][c][p])return 0;
		else if (gain[r][c][i]==gain[r][c][p]) eq=1;
	}
	return eq;
}

int getid(int *tb){
	int res=0;
	for (int i=0; i<5; ++i) res=tb[i]+res*3;
	return res;
}
void build(int *tb, int id){
	REPV(i, 5) tb[i]=id%3, id/=3;
}

vector<vi> buildBoard(int r, int c, int disp=0){
	build(tcol, c); build(trow, r);
	//out(tcol, 5); out(trow, 5);
	vector<vi> eb=board;
	REP(i, n) REP(j, m) eb[i][j]=(eb[i][j]+tcol[j]+trow[i])%3;
	if (disp){
	REP(i, n){ REP(j, m) printf("%d", eb[i][j]); printf("\n");}
	printf("\n");
	}
	return eb;
}

pii proc(int r, int c, int t){

	if (seen[r][c][t]) return dp[r][c][t];
	seen[r][c][t]=1;
	pii &p=dp[r][c][t];


	if (t==nt){
		vector<vi> eb=buildBoard(r, c);
		REP(i, n) REP(j, m) if (board[i][j]!=-1) ++gain[r][c][eb[i][j]];
		return p=MP(r, c);
	}
	int col[maxn], row[maxn];
	build(col, c); build(row, r);
	
	int w=-1, points=-1;
	bool take;
	int wa;
	pii np;
	REP(i, n-1){
		memcpy(trow, row, sizeof(row));

		REP(j, i+1) trow[j]=(trow[j]+inc)%3;
		np=proc(getid(trow), c, t+1);
		wa=win(np.ST, np.ND, t%3);
		//printf("%d %d\n", wa, gain[np.ST][np.ND][t%3]);

		take=0;
		if (w<wa) take=1;
		else if (w==wa && points<gain[np.ST][np.ND][t%3]) take=1;
		if (take){ w=wa; points=gain[np.ST][np.ND][t%3]; p=np;}
	}

	REP(i, n-1){
		take=0;
		memcpy(trow, row, sizeof(row));
		FOR(j, i+1, n-1) trow[j]=(trow[j]+inc)%3;
		np=proc(getid(trow), c, t+1);
		wa=win(np.ST, np.ND, t%3);

		take=0;
		if (w<wa) take=1;
		else if (w==wa && points<gain[np.ST][np.ND][t%3]) take=1;
		if (take){ w=wa; points=gain[np.ST][np.ND][t%3]; p=np;}

	}
	REP(i, m-1){
		memcpy(tcol, col, sizeof(col));
		REP(j, i+1) tcol[j]=(tcol[j]+inc)%3;
		np=proc(r, getid(tcol), t+1);
		wa=win(np.ST, np.ND, t%3);

	//	if (t==0){
	//		buildBoard(np.ST, np.ND, 1);
	//	printf("%d %d === %d %d => %d %d\n", w, points, wa, gain[np.ST][np.ND][t%3], r, getid(tcol));
	//	REP(j, 3) printf("%d \n", gain[np.ST][np.ND][t%3]);
	//	}
		take=0;
		if (w<wa) take=1;
		else if (w==wa && points<gain[np.ST][np.ND][t%3]) take=1;
		if (take){ w=wa; points=gain[np.ST][np.ND][t%3]; p=np;}

	}REP(i, m-1){

		take=0;
		memcpy(tcol, col, sizeof(col));
		FOR(j, i+1, m-1) tcol[j]=(tcol[j]+inc)%3;
		np=proc(r, getid(tcol), t+1);
		wa=win(np.ST, np.ND, t%3);

		take=0;
		if (w<wa) take=1;
		else if (w==wa && points<gain[np.ST][np.ND][t%3]) take=1;
		if (take){ w=wa; points=gain[np.ST][np.ND][t%3]; p=np;}
	}


	//if (t==0)
	//printf("take %d %d\n", w, points);
	return p;
}

class Inc {
	public:
		vector <string> finalBoard(vector <string> ib, int _inc, int _nt) {
			nt=_nt; inc=_inc;

			if (inc==-1) inc=2;
			n=ib.size(); m=ib[0].length();
			board=vector<vi>(n, vi(m));
			REP(i, n) REP(j, m) board[i][j]=(ib[i][j]=='.'?-1:ib[i][j]-'1');

			memset(gain, 0, sizeof(gain));
			memset(seen, 0, sizeof(seen));
		//	proc(0, 234, 1);
			pii z=proc(0, 0, 0);
		//	return vs();
			vector<vi> res=buildBoard(z.ST, z.ND);

			vs a(n, string(m, '.'));
			REP(i, n) REP(j, m) a[i][j]=(board[i][j]==-1?'.':res[i][j]+'1');
			return a;
		}

		// BEGIN CUT HERE
	public:
		void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
		template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
		void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
		void test_case_0() { string Arr0[] = { "333",
			"3.3",
			"333" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 1; string Arr3[] = {"111", "1.1", "333" }; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(0, Arg3, finalBoard(Arg0, Arg1, Arg2)); }
		void test_case_1() { string Arr0[] = { "....",
			"3333",
			"3333",
			".33." }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; int Arg2 = 3; string Arr3[] = {"....", "2222", "2222", ".22." }; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(1, Arg3, finalBoard(Arg0, Arg1, Arg2)); }
		void test_case_2() { string Arr0[] = { "111", "111" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 9; string Arr3[] = {"313", "232" }; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(2, Arg3, finalBoard(Arg0, Arg1, Arg2)); }
		void test_case_3() { string Arr0[] = { "2222", "2222", "2222" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; int Arg2 = 2; string Arr3[] = {"3112", "3112", "3112" }; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(3, Arg3, finalBoard(Arg0, Arg1, Arg2)); }
		void test_case_4() { string Arr0[] = { "231.3",
			"3.233",
			"12.12",
			"3.231",
			"132.3" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 10; string Arr3[] = {"123.1", "1.333", "12.31", "1.331", "132.2" }; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(4, Arg3, finalBoard(Arg0, Arg1, Arg2)); }
		void test_case_5() { string Arr0[] = {
			"123",
			"123"
		}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 1; string Arr3[] = {"131", "131" }; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(5, Arg3, finalBoard(Arg0, Arg1, Arg2)); }

		// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	Inc ___test; 
	___test.run_test(-1);
} 
// END CUT HERE

// BEGIN CUT HERE

// END CUT HERE
#line 5 "CheckersBoard.cpp"

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

int n;
int in(int x, int y){return x>=0 && y>=0 && x<n && y<n;}


class CheckersBoard {
	public:
	int numMoves(vector <string> board) {
        n=8;
        int cnta[2], cntb[2];
        int jmp[2];
        cnta[0]=cnta[1]=0;
        cntb[0]=cntb[1]=0;
        jmp[0]=jmp[1]=0;
        REP(i, n) REP(j, n) if (board[i][j]!=' '){
            int id=board[i][j]=='B';
            int vy=(id?1:-1);
            for (int k=-1; k<=1; k+=2) if (in(i+vy, j+k)){
                if (board[i+vy][j+k]==' ') ++cntb[id];
                else if (board[i+vy][j+k]!=board[i][j] && in(i+2*vy, j+2*k) && board[i+2*vy][j+2*k]==' ') ++cnta[id];

            }


        }
        return (cnta[0]?cnta[0]:cntb[0])+(cnta[1]?cnta[1]:cntb[1]);
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {
"B       ",
"        ",
"        ",
"        ",
"        ",
"        ",
"        ",
" W      "
}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(0, Arg1, numMoves(Arg0)); }
	void test_case_1() { string Arr0[] = {
"B B     ",
" W      ",
"        ",
"        ",
"        ",
"        ",
"        ",
"        "
}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(1, Arg1, numMoves(Arg0)); }
	void test_case_2() { string Arr0[] = {
"B B B B ",
" B B B B",
"B B B B ",
"        ",
"        ",
" W W W W",
"W W W W ",
" W W W W"
}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 14; verify_case(2, Arg1, numMoves(Arg0)); }
	void test_case_3() { string Arr0[] = {
"B B B B ",
" W W W W",
"W W W W ",
"        ",
"        ",
"        ",
"        ",
"        "
}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(3, Arg1, numMoves(Arg0)); }
	void test_case_4() { string Arr0[] = {
"    B B ",
"   B B W",
"    B W ",
"     W W",
"      W ",
"       W",
"        ",
"        "
}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(4, Arg1, numMoves(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  CheckersBoard ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE

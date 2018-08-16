// BEGIN CUT HERE

// END CUT HERE
#line 5 "STable.cpp"

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
typedef vector<string> vs;

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


const int maxn=33;
ll dp[maxn][maxn];
int x;
int graph[maxn*maxn][maxn*maxn];
pii prev[maxn*maxn][2];
char letter[maxn][maxn];
string s, t;


int id(int a, int b){return a*x+b;}
char getl(int xa, int ya){
    char &r=letter[xa][ya];
    if (r!=-1) return r;
    if (!xa) r=t[ya-1];
    else if (!ya) r=s[xa-1];
    else r=min(getl(xa-1, ya), getl(xa, ya-1));
    return r;

}
int proc(int xa, int ya, int xb, int yb){

    int ia, ib;
    int a=id(xa, ya), b=id(xb, yb);
    int &r=graph[a][b];
    if (r!=-1) return r;

    if (!xa||!ya||!xb||!yb) return r=getl(xa, ya)<=getl(xb, yb);
    ia=proc(prev[a][1].ST, prev[a][1].ND, prev[a][0].ST, prev[a][0].ND);
    ib=proc(prev[b][1].ST, prev[b][1].ND, prev[b][0].ST, prev[b][0].ND);
    if (prev[a][ia]==prev[b][ib]) ia^=1, ib^=1;
    return r=proc(prev[a][ia].ST, prev[a][ia].ND, prev[b][ib].ST, prev[b][ib].ND);
}


string query(int a, int b, ll x, ll y){
    checkmax(x, 0LL);
    checkmin(y, dp[a][b]);
    int z=id(a, b);
    if (x>=y) return "";


    if (a==0){assert(y==x+1); return string(1, t[b-1]);}
    else if(b==0){assert(y==x+1); return string(1, s[a-1]);}

    if (proc(a-1, b, a, b-1)) return query(a-1, b, x, y)+query(a, b-1, x-dp[a-1][b], y-dp[a-1][b]);
    else return query(a, b-1, x, y)+query(a-1, b, x-dp[a][b-1], y-dp[a][b-1]);
}


class STable {
	public:
	string getString(string _s, string _t, long long pos) {
        s=_s; t=_t;
        int m=t.length();
        int n=s.length();
        x=max(n, m)+1;


        memset(letter, -1, sizeof(letter));
        memset(graph , -1, sizeof(graph));

        REP(i, x) dp[i+1][0]=dp[0][i+1]=1;
        REP(i, x) REP(j, x) dp[i+1][j+1]=dp[i][j+1]+dp[i+1][j];

        FOR(i, 1, x-1) FOR(j, 1, x-1) prev[id(i,j)][0]=MP(i,j-1), prev[id(i,j)][1]=MP(i-1,j);
        return query(n, m, pos, min(pos+50, dp[n][m]));
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "ad"; string Arg1 = "cb"; long long Arg2 = 0LL; string Arg3 = "acbacd"; verify_case(0, Arg3, getString(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arg0 = "fox"; string Arg1 = "cat"; long long Arg2 = 0LL; string Arg3 = "acfcfoacftacfcfocfox"; verify_case(1, Arg3, getString(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arg0 = "Ra6b1t"; string Arg1 = "W0lf"; long long Arg2 = 66LL; string Arg3 = "RWab0RWRWa0RWl0RWRWa6RWa0RWRWa6RWa6RWab0RWRWa6RWa6"; verify_case(2, Arg3, getString(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arg0 = "M0HAXG"; string Arg1 = "COFU12"; long long Arg2 = 919LL; string Arg3 = "MOFU2"; verify_case(3, Arg3, getString(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arg0 = "a0B1c2D3e4F5gHiJkLmN"; string Arg1 = "A9b8C7d6EfGhIjKlMn"; long long Arg2 = 9876543210LL; string Arg3 = "B10AaB1c0Aa9Aa0AaB0AaB10AaB1c0AaB1c20Aa9Aa0AaB0Aa9"; verify_case(4, Arg3, getString(Arg0, Arg1, Arg2)); }
	void test_case_5() { string Arg0 = "TCOR2"; string Arg1 = "MEDiUm"; long long Arg2 = 350LL; string Arg3 = "MTDEMTiCMTEMTDEMTDEMTiDEMTiUCMTEMTCMTOCMTEMTDEMTCM"; verify_case(5, Arg3, getString(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  STable ___test; 
        ___test.run_test(-1);
        } 
// END CUT HERE

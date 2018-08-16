// BEGIN CUT HERE

// END CUT HERE
#line 5 "MapFolder.cpp"

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


const int maxn=51;
int n, m;
int foldv[maxn][maxn];
int foldh[maxn][maxn];
int dp[maxn][maxn][maxn][maxn];

int solve(int x, int y, int nx, int ny){
    if (nx==1 && ny==1) return 0;
    int &r=dp[x][y][nx][ny];
    if (r!=-1) return r;

    r=-2;

    REP(i, nx-1){
        int sz=min(i+1, nx-1-i);
        int tmp=foldv[x+i][y];
        int ok=1;
        FOR(j, y, ny-1) if (tmp!=foldv[x+i][j]){ok=0; break;}
        if (!ok) continue;

        REP(k, sz) if (ok) FOR(j, y, y+ny-2) if (foldh[x+i-k][j]==foldh[x+i+k+1][j]){ok=0; break;}
        if (!ok) continue;
        FOR(k, 1, sz-1) if (ok) FOR(j, y, y+ny-1) if (foldv[x+i-k][j]==foldv[x+i+k][j]){ok=0; break;}
        if (!ok) continue;
        int nr;
        if (sz==i+1) nr=solve(x+sz, y, nx-sz, ny)+1;
        else nr=solve(x, y, nx-sz, ny)+1;
        if (nr!=-1 && (r==-2 || nr<r)) r=nr;
    }

    REP(i, ny-1){
        int sz=min(i+1, ny-1-i);
        int tmp=foldh[x][y+i];
        int ok=1;
        FOR(j, x, x+nx-1) if (tmp!=foldh[j][y+i]){ok=0; break;}
        if (!ok) continue;

        REP(k, sz) if (ok) FOR(j, x, x+nx-2) if (foldv[j][y+i-k]==foldv[j][y+i+k+1]){ok=0; break;}
        if (!ok) continue;
        FOR(k, 1, sz-1) if (ok) FOR(j, x, x+nx-1) if (foldh[j][y+i-k]==foldh[j][y+i+k]){ok=0; break;}
        if (!ok) continue;
        int nr;
        if (sz==i+1) nr=solve(x, y+sz, nx, ny-sz)+1;
        else nr=solve(x, y, nx, ny-sz)+1;
        if (nr!=-1 && (r==-2 || nr<r)) r=nr;
    }
    return r;

}

class MapFolder {
	public:
	int minFolds(vector <string> ma) {
        n=ma.size();
        m=ma[0].size();

        REP(i, n/2+1) REP(j, m) foldv[j][i]=(ma[2*i][j]=='u');
        REP(i, n/2) REP(j, m+1) foldh[j][i]=(ma[2*i+1][j]=='u');
        memset(dp, -1, sizeof(dp));
        int res=solve(0, 0, m+1, n/2+1);
        return (res==-2?-1:res);
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"uud","uudd","duu"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(0, Arg1, minFolds(Arg0)); }
	void test_case_1() { string Arr0[] = {"uud","uudu","dud"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(1, Arg1, minFolds(Arg0)); }
	void test_case_2() { string Arr0[] = {"d"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(2, Arg1, minFolds(Arg0)); }
	//void test_case_3() { string Arr0[] = {"uuuuuuuuuuuuuuuuuuuuu","ududududududududududud","uuuuuuuuuuuuuuuuuuuuu"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 22; verify_case(3, Arg1, minFolds(Arg0)); }
	void test_case_3() { string Arr0[] = {"duuddudduddduuddduuuduu", "ddddduuuuuuuuuuddddddddd", "uddudduuduuuddduudddudd", "dduududduuddddduuuuudduu", "dduuddduuudduuddduudddu", "ddddduuuuuuuuuuddddddddd", "uuddduuddduuddduudduuud", "uudduduudduuuuuddddduudd", "duuddudduddduuddduuuduu", "uuuuudddddddddduuuuuuuuu", "uddudduuduuuddduudddudd", "dduududduuddddduuuuudduu", "dduuddduuudduuddduudddu", "dduududduuddddduuuuudduu", "uddudduuduuuddduudddudd", "uudduduudduuuuuddddduudd", "dduuddduuudduuddduudddu", "uudduduudduuuuuddddduudd", "uddudduuduuuddduudddudd", "uudduduudduuuuuddddduudd", "dduuddduuudduuddduudddu", "uuddduuuddddddduuuuuuudd", "udddduuudduuddduudduudd", "dddddddddddddddddddddddd", "duuuuddduudduuudduudduu", "dduuuddduuuuuuuddddddduu", "uudduuuddduudduuudduuud", "uuuuuuuuuuuuuuuuuuuuuuuu", "dduuddduuudduuddduudddu", "uuddduuuddddddduuuuuuudd", "udddduuudduuddduudduudd", "uuuuuuuuuuuuuuuuuuuuuuuu", "duuuuddduudduuudduudduu", "dduuuddduuuuuuuddddddduu", "uudduuuddduudduuudduuud", "dduududduuddddduuuuudduu", "duuduudduddduuudduuuduu", "dduududduuddddduuuuudduu", "uudduuuddduudduuudduuud", "dduududduuddddduuuuudduu", "duuduudduddduuudduuuduu", "uudduduudduuuuuddddduudd", "uudduuuddduudduuudduuud", "uudduduudduuuuuddddduudd", "duuduudduddduuudduuuduu"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 22; verify_case(3, Arg1, minFolds(Arg0)); }
	void test_case_4() { string Arr0[] = {"u", "uu", "u"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(4, Arg1, minFolds(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  MapFolder ___test; 
        ___test.run_test(3);
        } 
// END CUT HERE

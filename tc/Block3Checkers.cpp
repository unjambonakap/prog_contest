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
#define FOR(i, a, b) for(int i = (int)(a); i < (int)(b); ++i)

#define FE(i,t) for (__typeof((t).begin())i=(t).begin();i!=(t).end();++i)
#define FEV(i,t) for (__typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();++i)

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
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int maxn=22;
const int oo=1e9;
char mp[maxn][maxn];
int type[maxn][maxn];
int dist[maxn][maxn];
int rmp[maxn][maxn];

int r,c;
vector<pii> order;
int cost[3][maxn][maxn];
int g[3][3];

int in(int a, int b){return a>=0&&b>=0&&a<r&&b<c;}

void go(int a){
    priority_queue<pair<int,pii> > q;
    memset(dist,0x7f,sizeof(dist));
    REP(i,r) REP(j,c) if (type[i][j]==a) dist[i][j]=mp[i][j]!='N', q.push(MP(-dist[i][j],MP(i,j)));

    while(q.size()){
        int d=-q.top().ST;
        int x=q.top().ND.ST, y=q.top().ND.ND; q.pop();
        if (d!=dist[x][y])continue;

        FOR(nx,x-1,x+2) FOR(ny,y-1,y+2) if (in(nx,ny) && (x!=nx || y!=ny) && mp[nx][ny]!='A'){
            int c=mp[nx][ny]!='N';
            if (dist[nx][ny]>d+c) dist[nx][ny]=d+c, q.push(MP(-dist[nx][ny],MP(nx,ny)));
        }
    }
    memcpy(cost[a],dist,sizeof(dist));
    REP(k,2){
        int b=(a+k+1)%3;
        REP(i,r) REP(j,c) if (type[i][j]==b) g[a][b]=min(g[a][b],dist[i][j]);
    }
}

int go2(){
    int res=oo;
    REP(i,r) REP(j,c) if (mp[i][j]!='A'){
        int x=mp[i][j]!='N'?2:0;
        res=min(res,cost[0][i][j]+cost[1][i][j]+cost[2][i][j]-x);
    }
    return res;
}

int solve(){
    order.clear();

    REP(i,r) order.pb(MP(i,0));
    REP(i,c-1) order.pb(MP(r-1,i+1));
    REPV(i,r-1) order.pb(MP(i,c-1));
    REPV(i,c-2) order.pb(MP(0,i+1));

    vi pos;
    REP(i,order.size()) if (mp[order[i].ST][order[i].ND]=='A') pos.pb(i);
    pos.pb(pos[0]+order.size());

    REP(i,3) if (pos[i+1]==pos[i]+1) return oo;
    REP(i,order.size()) rmp[order[i].ST][order[i].ND]=i;

    memset(type,-1,sizeof(type));
    REP(i,3) FOR(j,pos[i]+1,pos[i+1]) type[order[j%order.size()].ST][order[j%order.size()].ND]=i;

    memset(g,0x1f,sizeof(g));
    REP(i,3) go(i);

    int res=go2();
    REP(i,3) res=min(res,g[i][(i+1)%3]+g[i][(i+2)%3]);
    return res;
}


class Block3Checkers{ 
    public: 
    int blockThem(vector <string> board){ 
        r=board.size();
        c=board[0].size();
        REP(i,r) REP(j,c) mp[i][j]=board[i][j];
        return min(100,solve());
    } 
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"A......A",
 "...N.N..",
 ".NNN.NN.",
 "NNNN.N.N",
 "N.NN.NNN",
 ".NNN.NNN",
 "NNN...NN",
 ".NN.A..N"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, blockThem(Arg0)); }
	void test_case_1() { string Arr0[] = {".....A",
 "......",
 "......",
 "NNNNNN",
 "A.....",
 "A....."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 100; verify_case(1, Arg1, blockThem(Arg0)); }

//	void test_case_2() { string Arr0[] = {"A.N",
// "NNA",
// "AN."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(2, Arg1, blockThem(Arg0)); }

	void test_case_2() { string Arr0[] = 
{"............",
"A...........",
"............",
"............",
"...........A",
"............",
"............",
"............",
"............",
"............",
"............",
".A.........."}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(2, Arg1, blockThem(Arg0)); }

	void test_case_3() { string Arr0[] = {"......NA",
 ".NNNN.N.",
 ".N......",
 "....NNNN",
 "........",
 ".N..NNN.",
 "......N.",
 "A.N....A"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(3, Arg1, blockThem(Arg0)); }

// END CUT HERE
 
}; 

// BEGIN CUT HERE 
int main(){
    Block3Checkers ___test;
    ___test.run_test(2);
} 
// END CUT HERE

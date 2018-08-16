// BEGIN CUT HERE

// END CUT HERE
#line 5 "PrinceXDominoes.cpp"

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

const int maxn=30;
const int maxe=4*maxn*maxn;
const int inf=1e6;
int vis[maxe];
int g[maxn][maxn];
int n;

struct MFMC{
    int cost[maxe], f[maxe], u[maxe], from[maxe], to[maxe], last[maxe], prev[maxe];
    int n,m;
    int d[2*maxe];
    int fc;
    int par[2*maxe];
    int vis[2*maxe];
    int tb[2*maxe];
    int step;

    MFMC(int n):n(n),m(0){memset(vis,0,sizeof(vis)); step=0; memset(par,0,sizeof(par)); }


    int adde(int a, int b, int cx, int ux){
        assert(a<maxn && b<maxn);
        cost[m]=cx; f[m]=0; u[m]=ux; from[m]=a; to[m]=b; prev[m]=last[a]; last[a]=m; ++m;
        cost[m]=-cx; f[m]=0; u[m]=0; from[m]=b; to[m]=a; prev[m]=last[b]; last[b]=m; ++m;
        assert(m<=maxe);
        return m-2;
    }

    int go(){
        fc=0;
        while(1){
            memset(d,0,sizeof(d));
            memset(par,-1,sizeof(par));

            REP(_step,n-1){
                int fd=0;
                REP(i,m) if (f[i]<u[i] && d[to[i]]>d[from[i]]+cost[i]){
                    par[to[i]]=i;
                    fd=1;
                    d[to[i]]=d[from[i]]+cost[i];
                }
                if (!fd) break;
            }
            int fd=0;
            REP(i,m) if (f[i]<u[i] && d[to[i]]>d[from[i]]+cost[i]){//negative cycle
                int p=i;
                par[to[i]]=p;
                ++step;
                vis[to[i]]=step;
                int sz=0;
                tb[sz++]=p;  p=par[from[p]];
                int mc=u[p]-f[p];
                while(vis[to[p]]!=step){int y=par[from[p]]; checkmin(mc,u[y]-f[y]); tb[sz++]=p; vis[to[p]]=step;  p=y; }
                int x=from[p];
                for (int i=sz-1; i>=0; --i){
                    int y=tb[i];
                    fc+=mc*cost[y];
                    f[y]+=mc; f[y^1]-=mc;
                    if (from[y]==x) break;
                }
                fd=1;
                break;
            }
            if (!fd) return fc;
        }

        return fc;
    }
};



void dfs(int a){
    if (vis[a]) return;
    vis[a]=1;
    REP(i,n) if (g[a][i]) dfs(i);
}

class PrinceXDominoes {
    public:
        int play(vector <string> d) {
            memset(vis,0,sizeof(vis));
            memset(g,0,sizeof(g));
            n=d.size();
            REP(i,n) REP(j,n) if (d[i][j]=='.'); else g[i][j]=d[i][j]-'A'+1;
            dfs(0);
            REP(i,n) if (!vis[i]) return -1;


            MFMC mf(n);
            int best=0;
            REP(i,n) REP(j,n) if (g[i][j]){
                mf.adde(i,j,-inf,1);
                ++best;
                if (g[i][j]>1) mf.adde(i,j,-1,g[i][j]-1);
            }
            int res=mf.go();
            if (res>-best*inf) return -1;
            return -res-best*inf+best;
        }

        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }

        void test_case_0() { string Arr0[] = {"MINI", ".BNP", "ILN.", "QPOH"} ; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(0, Arg1, play(Arg0)); }
        //void test_case_0() { string Arr0[] = {".A." ,"..B" ,"A.A"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(0, Arg1, play(Arg0)); }
        void test_case_1() { string Arr0[] = {"A.." ,".B." ,"..C"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(1, Arg1, play(Arg0)); }
        void test_case_2() { string Arr0[] = {"ZZ"
            ,"ZZ"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 104; verify_case(2, Arg1, play(Arg0)); }
        void test_case_3() { string Arr0[] = {"THIS.SRM"
            ,"IS.SPONS"
                ,"ORED.BY."
                ,"CITI.THA"
                ,"NKS.FOR."
                ,"PARTICIP"
                ,"ATING.DO"
                ,"LPHINIGL"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 612; verify_case(3, Arg1, play(Arg0)); }
        void test_case_4() { string Arr0[] = {"A.A.A.A.A."
            ,"DOLPHINIGL"
                ,"A.Z.X.D.F."
                ,"IVANMETELS"
                ,"T.W.W.X.M."
                ,"RNGRNGRNGR"
                ,"W.S.C.E.F."
                ,"FUSHARFUSH"
                ,"A.B.C.D.E."
                ,"CITICITICI"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(4, Arg1, play(Arg0)); }

        // END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
    PrinceXDominoes ___test; 
    ___test.run_test(-1); 
} 
// END CUT HERE

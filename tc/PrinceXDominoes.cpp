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

const int maxn=33;
const int maxe=2*maxn*maxn+2*maxn;
int vis[maxn];
int g[maxn][maxn];
int n;

struct MaxFlow{
    int last[maxn];
    int prev[maxe];
    int to[maxe];
    int u[maxe];
    int f[maxe];
    int from[maxe];
    int c[maxe];

    int s, t;
    int fc;

    int dist[maxn];
    int par[maxn];

    int n, ne;
    MaxFlow(int n):n(n){
        memset(last, -1, sizeof(last));
        memset(u, 0, sizeof(u));
        ne=0;
        s=n-2; t=n-1;
        fc=0;

    }
    void adde(int a, int b, int cost, int cap){
        from[ne]=a; prev[ne]=last[a]; to[ne]=b; u[ne]=cap; f[ne]=0; c[ne]=cost; last[a]=ne++;
        swap(a,b);
        from[ne]=a; prev[ne]=last[a]; to[ne]=b; u[ne]=0; f[ne]=0; c[ne]=-cost; last[a]=ne++;
    }

    int go(){
        memset(dist,0x7f,sizeof(dist));
        dist[s]=0;
        par[s]=-1;

        REP(step,n-1){
            int fd=0;
            REP(j,ne) if (u[j]>f[j] && dist[to[j]]>dist[from[j]]+c[j]) dist[to[j]]=dist[from[j]]+c[j], par[to[j]]=j, fd=1;
            if (!fd) break;
        }
        if (dist[t]<1e9){
            fc+=dist[t];
            int x=t;
            while(par[x]!=-1){int nx=par[x]; ++f[nx]; --f[nx^1]; x=from[nx];}
            return 1;
        }
        return 0;
    }

};

int da[maxn], db[maxn];
const int inf=11111;


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


            memset(da,0,sizeof(da)); memset(db,0,sizeof(db));
            REP(i,n) REP(j,n) da[i]+=g[i][j], db[j]+=g[i][j];

            MaxFlow mf(n+2);
            int s=n, t=n+1;
            int na=0;
            REP(i,n){
                if (da[i]>db[i]) mf.adde(s,i,1,da[i]-db[i]), na+=da[i]-db[i];
                else mf.adde(i,t,1,db[i]-da[i]);
            }
            REP(i,n) REP(j,n) mf.adde(i,j,1,max(0,g[i][j]-1));


            int res=0;
            REP(i,n) REP(j,n) res+=g[i][j];
            REP(i,na) if (!mf.go()){
                return -1;
            }
            return res-(mf.fc-2*na);

        }

        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
        void test_case_0() { string Arr0[] = {"BIQMWPP.JXGUUWAOMAEJYGALK", "SKBDABFTDXLLH..OBFQXEDVUE", "HBQBDOCCRPERFBDVUXIEH.LWX", "MVUT.QHDV.QQMNVQOQTYETTSZ", "BGMJXN.WNATMDUWVMPTBGEZAA", "AGKBVURNBGQZJJFLGENTQKWAD", "PIEKGESAFXBWMHBYDEFJIVYM.", "M.XYCURVHUEDVDQNPZQLUZLNF", "U.VUTLJHBZLABJOZKJHRNSULN", "IRJF.TT.RFIPPDHOVDAJJZSCY", "UTYFOYCRYDCPMLADYOPSJFFXP", "MGKCIIWGCHCEZ.ZYMSWXYPVWQ", "OFCMFDSBTCEU.UMEC.PRHJKLM", "CULRXDGMOPBDWFZRGWTMYBQIV", "RMWJYIBODPGKKINECBUHNPFCS", "ILIDNBQESXMLEKKMG.NXRZCUX", "VDTUDQIHSRRCAHIQLAHOTAGQB", "OUKWSRNAQWHNXMDLHPTQSVDCW", "GOGEKWBZUDFWYVLSBDQALVFPA", "XUKPDNGGX.EAFMI.LGARBRRAT", "CGHOWXHSPQONQOHGLVOJQSRLR", "LAUZNQSVEZOX.BIZKSCHXKUZL", "IIBVNVDP.UNKNTVMCMSCSZEPS", "PHAYCQKFPSBTZNEPAWZFWNC.M", ".HZLHVWPVKAIHTOHOLYKFOZLC"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(0, Arg1, play(Arg0)); }
        //void test_case_0() { string Arr0[] = {".A." ,"..B" ,"A.A"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(0, Arg1, play(Arg0)); }
        void test_case_1() { string Arr0[] = {"A.."
            ,".B."
                ,"..C"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(1, Arg1, play(Arg0)); }
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

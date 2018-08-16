// BEGIN CUT HERE

// END CUT HERE
#line 5 "RabbitWorking.cpp"

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

const int maxN=55;
const int maxn=maxN*maxN+maxN+2;
const int maxe=3*maxn;
const int inf=1e9;

int px[maxN][maxN];

int to[maxe], from[maxe], c[maxe], f[maxe], prev[maxe], last[maxn];
int dist[maxn];
int ne, n;
int N;
int par[maxn], vis[maxn];
int q[maxn];

void adde(int a, int b, int cx){
    from[ne]=a; to[ne]=b; c[ne]=cx; f[ne]=0; prev[ne]=last[a]; last[a]=ne++;
    swap(a,b); from[ne]=a; to[ne]=b; c[ne]=0; f[ne]=0; prev[ne]=last[a]; last[a]=ne++;
}

int dfs(int a, int p=-1){
    par[a]=p;
    if (a==1) return 1;
    for (int i=last[a]; i!=-1; i=prev[i]) if (f[i]<c[i] && dist[to[i]]==dist[a]+1 && dfs(to[i],i)) return 1;
    return 0;
}

void bfs(){
    int qa=0, qe=0;
    dist[0]=0;
    q[qe++]=0;
    while(qa<qe){
        int a=q[qa++];
        for (int i=last[a]; i!=-1; i=prev[i]) if (f[i]<c[i] && dist[to[i]]>dist[a]+1) q[qe++]=to[i], dist[to[i]]=dist[a]+1;
    }
}

ll mf(){
    ll res=0;
    while(1){
        memset(par,-1,sizeof(par));
        memset(dist,0x7f,sizeof(dist));
        bfs();
        if (dist[1]>inf) break;
        while(dfs(0)){
            int p=1, x=inf;
            while(p!=0) x=min(x,c[par[p]]-f[par[p]]), p=from[par[p]];
            res+=x;
            p=1;
            while(p!=0) f[par[p]]+=x, f[par[p]^1]-=x, p=from[par[p]];
        }
    }

    return res;
}

int checkit(int rb, int ra){
    ne=0;
    memset(last,-1,sizeof(last));
    ll u=0;
    REP(i,N) adde(2+i,1,199*rb);
    int pos=N+2;
    ll s=0;
    int st=ne;
    REP(i,N) REP(j,i) adde(0,pos,px[i][j]*ra+2*rb), adde(pos,i+2,inf), adde(pos,j+2,inf), ++pos, s+=px[i][j]*ra+2*rb;
    ll x=mf();
    return x<s;
}

class RabbitWorking {
    public:
        double getMaximum(vector <string> profit) {
            N=profit.size();
            REP(i,N) REP(j,N) px[i][j]=profit[i][j]-'0';

            vector<pair<double,pii> > tb;
            FOR(i,1,N+1) REP(j,9*i*(i-1)/2+1) tb.pb(MP(1.*j/(i*(200-i)),MP(j,i*(200-i))));
            sort(ALL(tb));


            int T=0, H=tb.size();
            int best=-1;
            while(T<=H){
                int M=T+H>>1;
                if (checkit(tb[M].ND.ST, tb[M].ND.ND)) best=M, T=M+1;
                else H=M-1;
            }

            return tb[best+1].ST;
        }

        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
        void test_case_0() { string Arr0[] = {"00010000000000000010000101000000001000100010000000", "00000100000000000000000000100000010000000000000000", "00000000000000000000000000000010000000000000001000", "10000000000000000000000000000010010000000010000010", "00000000000000000000000000001000000000000000100010", "01000000000000000010000000000000000000000000000000", "00000000000000000000000010000000010000000000000000", "00000000000000000000000000000000000010000000000001", "00000000000011000000000000000000000000100100000000", "00000000000000000000000000000000000000000000000000", "00000000000000000100000001000000000000000100000000", "00000000000000000000000010100000010000011000000110", "00000000100000000100000010000000000000000000000000", "00000000100000000000000000000000000000000000000000", "00000000000000000100001000000000000010000000100000", "00000000000000000010000000000000000000000000000100", "00000000000000000000000000000000000000000000000000", "00000000001010100000000000010000000000000001000000", "10000100000000010000000010000000100000000001000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000001000000001100000000000", "00000000000000000000000000000000000001000000000000", "00000000000000100000000008000000000090007001000000", "10000000000000000000000000000000000001000000001000", "00000010000110000010000000000000001000000000000000", "10000000001000000000008000100000000090008000000000", "01000000000100000000000001000000000000000000000000", "00000000000000000100000000000001100000000000000000", "00001000000000000000100000000000000010000000000000", "00000000000000000000000000000000000000000000000000", "00110000000000000000000000000000001000000000000000", "00000000000000000000000000010000000000000000000000", "00000000000000000010000000010000000000000000000000", "01010010000100000000000000000000000000000000000000", "10000000000000000000000010000010000000001000000000", "00000000000000000000000000000000000000000010000000", "00000001000000100000009009001000000000007100000000", "00000000000000000000110100000000000000000000000100", "10000000100000000000100000000000000000000000000000", "00000000000100000000000000000000000000000100000000", "00000000000100000000007008000000001070000000000010", "00000000101000000000000000000000000010010000000000", "10010000000000000000000000000000000100000000000000", "00000000000000000110001000000000000000000000000000", "00001000000000100000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00100000000000000000000100000000000000000000000000", "00000000000100010000000000000000000001000000000000", "00011000000100000000000000000000000000001000000000", "00000001000000000000000000000000000000000000000000"} ; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 0.017676767676767676; verify_case(0, Arg1, getMaximum(Arg0)); }
        //void test_case_0() { string Arr0[] = { "071", "702", "120" } ; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 0.017676767676767676; verify_case(0, Arg1, getMaximum(Arg0)); }
        void test_case_1() { string Arr0[] = { "061", 
            "602", 
            "120" }
            ; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 0.015228426395939087; verify_case(1, Arg1, getMaximum(Arg0)); }
            void test_case_2() { string Arr0[] = { "0" }
                ; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 0.0; verify_case(2, Arg1, getMaximum(Arg0)); }
                void test_case_3() { string Arr0[] = { "013040", 
                    "100010", 
                    "300060", 
                    "000008", 
                    "416000", 
                    "000800" }
                    ; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 0.021996615905245348; verify_case(3, Arg1, getMaximum(Arg0)); }
                    void test_case_4() { string Arr0[] = { "06390061", 
                        "60960062", 
                        "39090270", 
                        "96900262", 
                        "00000212", 
                        "00222026", 
                        "66761201", 
                        "12022610" }
                        ; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 0.06871794871794872; verify_case(4, Arg1, getMaximum(Arg0)); }

                        // END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
    RabbitWorking ___test; 
    ___test.run_test(-1); 
} 
// END CUT HERE

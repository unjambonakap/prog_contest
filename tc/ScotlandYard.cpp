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

const int maxn=55;
int n;
int ta[maxn][maxn], tb[maxn][maxn], tc[maxn][maxn];

int vis[maxn][maxn];
char g[maxn*maxn][maxn*maxn];
int deg[maxn*maxn];
int S[maxn*maxn];
int can[maxn];


void proc(int st, int i){
    int cnt=0;
    REP(j,n) if (ta[i][j]) ++cnt;
    if (cnt>=2) REP(j,n) REP(k,n) if (ta[i][j] && ta[i][k]) g[st][j*n+k]=1;

    cnt=0;
    REP(j,n) if (tb[i][j]) ++cnt;
    if (cnt>=2) REP(j,n) REP(k,n) if (tb[i][j] && tb[i][k]) g[st][j*n+k]=1;

    cnt=0;
    REP(j,n) if (tc[i][j]) ++cnt;
    if (cnt>=2) REP(j,n) REP(k,n) if (tc[i][j] && tc[i][k]) g[st][j*n+k]=1;
}
void build(){
    memset(g,0,sizeof(g));
    REP(i,n) REP(j,n) if (j!=i) {
        REP(a,n) REP(b,n){ 
            if (a==b) continue;
            if ( (ta[i][a]&&ta[j][b]) || (tb[i][a]&&tb[j][b]) || (tc[i][a]&&tc[j][b]) )
                g[i*n+j][a*n+b]=1;
        }
        proc(i*n+j,i);
        proc(i*n+j,j);
    }

    REP(i,n) proc(i*n+i,i);
}



int go(){
    queue<int> q;
    memset(can,0,sizeof(can));
    REP(i,n){
        REP(j,n) if (ta[i][j]||tb[i][j]||tc[i][j]) can[i]=1;

    }
    memset(S,0,sizeof(S));
    memset(deg,0,sizeof(deg));
    REP(i,n*n) REP(j,n*n) deg[i]+=g[i][j];
    REP(i,n*n) if (!deg[i]) q.push(i), S[i]=can[i/n]||can[i%n];

    int step=0;
    int best=0;
    while(q.size()){
        ++step;
        int a=q.front(); q.pop();
        best=max(best,S[a]);
        REP(i,n*n) if (g[i][a]){
            S[i]=max(S[i],S[a]+1);
            if (!--deg[i]) q.push(i); 
        }
    }
    if (step!=n*n) return -1;
    return best;

}


class ScotlandYard{ 
    public: 
        int maxMoves(vector <string> A, vector <string> B, vector <string> C){ 
            n=A.size();
            REP(i,n) REP(j,n) ta[i][j]=A[i][j]=='Y';
            REP(i,n) REP(j,n) tb[i][j]=B[i][j]=='Y';
            REP(i,n) REP(j,n) tc[i][j]=C[i][j]=='Y';

            build();
            return go();

        } 

        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
        void test_case_0() { string Arr0[] = {"NYN",
            "NNY",
            "NNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"NNN",
                "NNN",
                "NNN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"NNN",
                    "NNN",
                    "NNN"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 2; verify_case(0, Arg3, maxMoves(Arg0, Arg1, Arg2)); }
        void test_case_1() { string Arr0[] = {"NYY",
            "NNN",
            "NNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"NNN",
                "NNN",
                "NNN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"NNN",
                    "NNN",
                    "NNN"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 1; verify_case(1, Arg3, maxMoves(Arg0, Arg1, Arg2)); }
        void test_case_2() { string Arr0[] = {"NYYY",
            "YNYY",
            "YYNY",
            "YYYN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"NNNN",
                "NNNN",
                "NNNN",
                "NNNN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"NNNN",
                    "NNNN",
                    "NNNN",
                    "NNNN"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = -1; verify_case(2, Arg3, maxMoves(Arg0, Arg1, Arg2)); }
        void test_case_3() { string Arr0[] = {"NNY",
            "NNY",
            "NNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"NYN",
                "NNY",
                "NNN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"NNN",
                    "NNN",
                    "YNN"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 2; verify_case(3, Arg3, maxMoves(Arg0, Arg1, Arg2)); }
        void test_case_4() { string Arr0[] = {"NNN",
            "YNY",
            "NNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"NNN",
                "YNN",
                "YNN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"NNN",
                    "NNN",
                    "YYN"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = -1; verify_case(4, Arg3, maxMoves(Arg0, Arg1, Arg2)); }
        void test_case_5() { string Arr0[] = {"NNNNYNNNYY",
            "NNYNNYYYYY",
            "NNNNNNNNNN",
            "YYNNYYNNNY",
            "NNYNNNNNNN",
            "YNYNYNNNYN",
            "NNYNYNNNYN",
            "NNNNNNYNNN",
            "NNNNNNNNNN",
            "NNNNNNYNNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"NNYNNNYNNY",
                "YNYNNYYNYY",
                "NNNNNNNNNN",
                "YNYNNYNYNY",
                "NNYNNNNNYN",
                "YNYNYNYNYN",
                "NNYNNNNNNY",
                "YNYNNNNNNN",
                "NNNNNNNNNN",
                "NNYNYNNNNN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"NNNNNNNYNN",
                    "YNYNNNNNYN",
                    "NNNNNNNNNN",
                    "NYNNYNNNYY",
                    "NNYNNNNNNN",
                    "YNYNNNNNYY",
                    "NNNNYNNNYN",
                    "NNYNNNYNNN",
                    "NNNNNNNNNY",
                    "NNYNYNNNNN"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 21; verify_case(5, Arg3, maxMoves(Arg0, Arg1, Arg2)); }

        // END CUT HERE

}; 

// BEGIN CUT HERE 
int main(){
    ScotlandYard ___test;
    ___test.run_test(-1);
} 
// END CUT HERE

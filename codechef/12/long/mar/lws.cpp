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

const int maxn=2222;
char s[maxn];
int n;

int A[maxn][26], B[maxn][26], C[maxn][26], D[maxn][26];


int dp[maxn][26][26];
int go(int p, int a, int b){
    if (p==n) return 0;
    int &r=dp[p][a][b];
    if (r!=-1) return r;
    r=go(p+1,a,b);
    if (s[p]>=a) checkmax(r,go(p+1,s[p],b)+1);
    if (s[p]<=b) checkmax(r,go(p+1,a,s[p])+1);
    return r;
}

int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        scanf(" %s", s);
        n=strlen(s);
        REP(i,n) s[i]-='a';
        memset(A,0,sizeof(A)); memset(B,0,sizeof(B)); memset(C,0,sizeof(C)); memset(D,0,sizeof(D));
        REP(i,n){
            REP(j,s[i]) A[i+1][j]=A[i][j];
            FOR(j,s[i],26) A[i+1][j]=max(A[i][j],A[i][s[i]]+1);

            FOR(j,s[i]+1,26) B[i+1][j]=B[i][j];
            REP(j,s[i]+1) B[i+1][j]=max(B[i][j],B[i][s[i]]+1);
        }
        REPV(i,n){
            FOR(j,s[i],26) C[i][j]=C[i+1][j];
            REP(j,s[i]+1) C[i][j]=max(C[i+1][j], C[i+1][s[i]]+1);

            REP(j,s[i]) D[i][j]=D[i+1][j];
            FOR(j,s[i],26) D[i][j]=max(D[i+1][j],D[i+1][s[i]]+1);
        }

        int ans=0;
        REP(i,n) REP(j,26){
            //int j=s[i];
            checkmax(ans, A[i+1][j]+(j+1==26?0:C[i+1][j+1])+(j+1==26?0:B[i+1][j+1])+D[i+1][j]);
            checkmax(ans, (!j?0:A[i+1][j-1])+C[i+1][j]+B[i+1][j]+(!j?0:D[i+1][j-1]));

            checkmax(ans, A[i+1][j]+C[i+1][j]+(j+1==26?0:B[i+1][j+1])+(!j?0:D[i+1][j-1]));
            checkmax(ans, B[i+1][j]+D[i+1][j]+(j+1==26?0:C[i+1][j+1])+(!j?0:A[i+1][j-1]));
        }
        cout<<ans<<endl;

    }
    return 0;
}



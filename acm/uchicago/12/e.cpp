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

const int maxn=2048;
const int maxk=25;
const int inf=1e8;



int n, K;
int A[maxn];
int B[maxn][maxn];
int F[maxn];
int dp[maxn][maxk];

int T[2*maxn], H[2*maxn], tree[2*maxn];
int val[maxn], rmp[maxn];
int pos[maxn];
int U[22][maxn];
int L, R;



int go(int a, int b){
    if (a==n) return 0;
    if (b==K) return inf;
    int &r=dp[a][b];
    if (r!=-1) return r;
    r=inf;
    FOR(i,a,n) checkmin(r,go(i+1,b+1)+B[a][i]);
    return r;
}

void med_init(int d, int a, int b){
    if (a+1==b){U[d][a]=U[d-1][a]; return;}
    int m=(a+b)/2;
    int u=a, v=m;
    FOR(i,a,b){
        if (rmp[U[d-1][i]]<m) U[d][u++]=U[d-1][i];
        else U[d][v++]=U[d-1][i];
    }
    med_init(d+1,a,m);
    med_init(d+1,m,b);

}

int med_query(int d, int a, int b, int u){
    if (a+1==b) return U[d][a];
    int m=a+b>>1;
    int T=a, H=m-1, besta, bestb;
    besta=inf;
    while(T<=H){
        int M=T+H>>1;
        if (U[d][M]<L) T=M+1;
        else H=M-1, besta=M;
    }
    T=a, H=m-1;
    bestb=-inf;
    while(T<=H){
        int M=T+H>>1;
        if (U[d][M]>R) H=M-1;
        else T=M+1, bestb=M;
    }
    int cnt=max(-1,bestb-besta);
    //out(U[d]+a,b-a); printf("%d %d %d %d FUUU (BD %d %d) %d %d %d \n", d,a,b,u,L,R,besta,bestb,cnt);
    return cnt<u?med_query(d+1,m,b,u-cnt-1):med_query(d+1,a,m,u);
}


void init(int x, int a, int b){
    T[x]=a; H[x]=b;
    if (a+1==b) return;
    init(2*x,a,(a+b)/2);
    init(2*x+1,(a+b)/2,b);
}

void add(int x, int a, int v){
    if (a<T[x] || H[x]<=a) return;
    tree[x]+=v;
    if (T[x]+1==H[x]) return;
    add(2*x,a,v); add(2*x+1,a,v);
}

int query2(int x, int a){
    if (a<T[x]) return 0;
    if (H[x]-1<=a) return tree[x];
    return query2(2*x,a)+query2(2*x+1,a);
}



int main(){
    init(1,0,maxn);

    while(cin>>n>>K,n){
        REP(i,n) scanf(" %d", A+i);

        F[0]=0;
        REP(i,n) F[i+1]=F[i]+A[i];


        REP(i,n) val[i]=A[i]; sort(val,val+n);
        REP(i,n) pos[i]=i;
        REP(i,n) rmp[i]=pos[lower_bound(val,val+n,A[i])-val]++;
        REP(i,n) U[0][i]=i;
        med_init(1,0,n);

        REP(i,n){
            memset(tree,0,sizeof(tree));
            FOR(j,i,n){
                //printf("ADD %d %d\n", rmp[j],A[j]);
                add(1,rmp[j],A[j]);
                int sz=j-i+1, sz2=sz/2;
                L=i; R=j;
                int med=med_query(1,0,n,sz2);
                B[i][j]=F[j+1]-F[i]-A[med]*(sz-sz2-1)+A[med]*(sz2+1)-2*query2(1,rmp[med]);
            }
        }
        memset(dp,-1,sizeof(dp));
        printf("%d\n", go(0,0));
    }
    return 0;
}




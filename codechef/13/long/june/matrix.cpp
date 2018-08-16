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
typedef unsigned int uint;
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

const int maxn=44;
//int tb[maxn][maxn];
//
//int seen[maxn];
//int n, res;
//void go(int a, int b){
//    if (a<=b) ++a, b=0;
//    if (a==n){
//        FOR(i,1,n-1) if (!seen[i]) return;
//
//        ++res;
//        puts("");
//        REP(i,n){
//            REP(j,n) printf("%d ",tb[i][j]);
//            puts("");
//        }
//        return;
//    }
//    FOR(i,1,n-1){
//        tb[a][b]=tb[b][a]=i;
//        REP(k,b){
//            int x=tb[k][b], y=tb[a][k];
//            int mx=max(x,max(y,i));
//            int cnt=(x==mx)+(y==mx)+(i==mx);
//            if (cnt==1) goto fail;
//
//        }
//        ++seen[i];
//        go(a,b+1);
//        --seen[i];
//fail:;
//    }
//    tb[a][b]=tb[b][a]=-1;
//}
//void gen(int N){
//    n=N;
//    memset(tb,-1,sizeof(tb));
//    REP(i,n) tb[i][i]=0;
//    res=0;
//    go(0,0);
//    cout<<res<<endl;
//}
//



int a[maxn], b[maxn];
int s2[maxn];
int px[maxn];
int st[maxn][maxn];

const int mod=1e9+7;
const int maxm=1e7+10;
const int maxa=1e5+10;

int tb[maxa];
int perm[maxa];
int res[maxa];


int cmp(int a, int b){return tb[a]<tb[b];}

int main(){
    if (0){
        //gen(5);
        REP(i,maxn) st[i][i]=1;
        FOR(i,1,maxn) FOR(j,1,i) st[i][j]=(1ll*st[i-1][j]*j+st[i-1][j-1])%mod;

        px[1]=1;
        FOR(i,2,maxn){
            a[i]=1ll*i*(i-1)/2%mod;
            px[i]=1ll*px[i-1]*a[i]%mod;
            s2[i]=(s2[i-1]+1ll*a[i]*(i-1))%mod;
        }

        FOR(i,3,20){
            b[i]=(1ll*b[i-1]*st[i][i-1]+1ll*px[i-2]*st[i][i-2])%mod;
            printf("%d\n",b[i]);
        }
    }

    int bench=0;

    int nq;
    if (!bench){
        cin>>nq;
        REP(qq,nq) scanf(" %d",tb+qq);
    }else{
        nq=0;
        FOR(i,3,20) tb[nq++]=i;
        tb[nq++]=1e7;
    }

    REP(i,nq) perm[i]=i;
    sort(perm,perm+nq,cmp);

    int u=2;
    int prod=1;
    int sum=0;
    int val=0;
    int prev=1;
    REP(i,nq){
        int v=tb[perm[i]];
        for (; u<v;){
            ++u;
            sum=(sum+1ll*prev*(u-2))%mod;
            int x=(1ll*u*(u-1)>>1)%mod;
            val=(1ll*val*x+1ll*prod*sum)%mod;
            prod=1ll*prod*prev%mod;
            prev=x;
        }
        res[perm[i]]=val;
    }
    REP(i,nq) printf("%d\n",res[i]);

    return 0;

}


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

const int maxb=22;
const int maxn=1e5+3*1e6+111;
const int oo=1e9;
const int minv='a'-1;



int rmp[2*maxn], tmp[maxn];
int lcp[maxb][maxn];
int A[maxn];
int X;
int n;
int V;
char buf[maxn];
int pos[maxn];
int F[maxn];

int na[maxn];
int nA[maxn];
int cnt[maxn];
int val[maxn];
int lst[maxn];



int cmp(int a, int b){
    int u=rmp[a], v=rmp[b];
    if (u!=v) return u<v;
    u=X+a<n?rmp[a+X]:-oo;
    v=X+b<n?rmp[b+X]:-oo;
    return u<v;
}


void rsort(int *a, int n){
    memset(cnt,0,sizeof(int)*V);
    //REP(i,n) val[i]=(a[i]+X<n?1+rmp[a[i]+X]:0), ++cnt[val[i]];
    REP(i,n) val[i]=rmp[a[i]+X], ++cnt[val[i]];
    REP(i,V) cnt[i+1]+=cnt[i];
    for (int i=n-1; i>=0; --i) nA[--cnt[val[i]]]=a[i];
 
    memset(cnt,0,sizeof(int)*V);
    REP(i,n) val[i]=rmp[nA[i]], ++cnt[val[i]];
    REP(i,V) cnt[i+1]+=cnt[i];
    for (int i=n-1; i>=0; --i) a[--cnt[val[i]]]=nA[i];
}

int main(){
    scanf(" %s", buf);
    int m; cin>>m;
    n=strlen(buf);
    int oldn=n;

    REP(i,m){
        buf[n++]='z'+1;
        scanf(" %s",buf+n);
        int x=strlen(buf+n);
        pos[i]=n; na[i]=x;
        REP(j,x-1) buf[n+x+j]=buf[n+j];
        n+=2*x-1;
    }

    buf[n++]='a'-1;
    buf[n++]='z'+2;
    V=256;;

    REP(i,n) rmp[i]=buf[i];

    for (int b=1; b<maxb; ++b){
        REP(i,n) A[i]=i;
        X=1<<(b-1);
        rsort(A,n);
        //stable_sort(A,A+n,cmp);
        tmp[A[0]]=1;
        REP(i,n-1){
            tmp[A[i+1]]=tmp[A[i]];
            if (cmp(A[i],A[i+1])) ++tmp[A[i+1]];
        }
        V=tmp[A[n-1]]+2;
        memcpy(rmp,tmp,sizeof(tmp));
    }
    REP(i,n) --rmp[i];
    REP(i,n) F[i+1]=F[i]+(A[i]<oldn);

    int u=0;
    A[n]=n-1;
    REP(i,n-2){
        int j=A[rmp[i]+1];

        if (i==j){printf("-1 on %d %d xx %d\n",i,j,n); return 0;}
        for (; buf[i+u]==buf[j+u]; ++u);
        lcp[0][rmp[i]]=u;
        if (u) --u;
    }
    for (int i=1; i<maxb; ++i) REP(j,n) lcp[i][j]=min(lcp[i-1][j],(j+(1<<i-1)>=n-1?0:lcp[i-1][j+(1<<i-1)]));


    REP(i,m){
        int res=0;
        REP(j,na[i]) lst[j]=rmp[pos[i]+j];
        sort(lst,lst+na[i]);
        REP(j,na[i]){
            int px=lst[j], nd=px, st=px;
            if (j){
                int u=oo,p=lst[j-1];
                for (int b=maxb-1; b>=0; --b) if (p+(1<<b)<px) u=min(u,lcp[b][p]), p+=1<<b;
                if (u>=na[i]) continue;
            }
            for (int b=maxb-1; b>=0; --b) if (lcp[b][nd]>=na[i]) nd+=1<<b;
            for (int b=maxb-1; b>=0; --b) if (st-(1<<b)>=0 && lcp[b][st-(1<<b)]>=na[i]) st-=1<<b;
            res+=F[nd+1]-F[st];
        }
        printf("%d\n",res);
    }


    return 0;
}


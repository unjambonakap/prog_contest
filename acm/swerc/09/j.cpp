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

const int maxb=17;
const int maxn=44446;
const int oo=1e9;



int rmp[maxn], tmp[maxn];
int lcp[maxb][maxn];
int rmq[maxb][maxn];
int A[maxn];
int X;
int n;
char buf[maxn];


int cmp(int a, int b){
    int u=rmp[a], v=rmp[b];
    if (u!=v) return u<v;
    u=X+a<n?rmp[a+X]:-oo;
    v=X+b<n?rmp[b+X]:-oo;
    return u<v;
}

int main(){

    int m;
    while(cin>>m,m){
        scanf(" %s",buf+2);
        n=strlen(buf+2);
        if (m==1){printf("%d %d\n",n,0); continue;}

        buf[0]='z'+1;
        buf[1]=-1;
        n+=2;
        REP(i,n) rmp[i]=buf[i];
        
        for (int b=1; b<maxb; ++b){
            REP(i,n) A[i]=i;
            X=1<<(b-1);
            sort(A,A+n,cmp);
            tmp[A[0]]=0;
            REP(i,n-1){
                tmp[A[i+1]]=tmp[A[i]];
                if (cmp(A[i],A[i+1])) ++tmp[A[i+1]];
            }
            memcpy(rmp,tmp,sizeof(rmp));
        }


        int u=0;
        A[n]=n-1;
        FOR(i,2,n){
            int j=A[rmp[i]+1];

            if (i==j){printf("-1\n"); return 0;}
            if (u<0) u=0;
            for (; buf[i+u]==buf[j+u]; ++u);
            lcp[0][rmp[i]]=u;
            --u;
        }
        for (int i=1; i<maxb; ++i) REP(j,n) lcp[i][j]=min(lcp[i-1][j],(j+(1<<i-1)>=n-1?0:lcp[i-1][j+(1<<i-1)]));
        REP(i,n) rmq[0][i]=A[i];
        for (int i=1; i<maxb; ++i) REP(j,n) rmq[i][j]=max(rmq[i-1][j],(j+(1<<i-1)>=n?0:rmq[i-1][j+(1<<i-1)]));

        int best=0, bestl=0;

        REP(i,n-m+1){
            int fd=0;
            int b=0;
            for (b=0; 1<<b<=m-1; ++b); --b;
            int val=min(lcp[b][i],lcp[b][i+m-1-(1<<b)]);
            for (b=0; 1<<b<=m; ++b); --b;
            if (val>bestl) bestl=val, best=-1;
            if (val==bestl) best=max(best,max(rmq[b][i],rmq[b][i+m-(1<<b)]));
        }

        if (bestl==0) puts("none");
        else printf("%d %d\n",bestl,best-2);
    }

    return 0;
}


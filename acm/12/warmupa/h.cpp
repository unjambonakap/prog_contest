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

const int maxn=1e5+10;
int n;
int next[maxn];
int vis[maxn];
int t[maxn], h[maxn];
int mx[maxn];
int q[maxn];
int prev[maxn];

ll dp[maxn];

ll go(int a){
    if (a==n) return 0;
    ll &r=dp[a];
    if (r!=-1) return r;
    r=min(go(next[a])+h[mx[a]],go(max(a+1,mx[a]))+prev[a]);
    return r;
}


int dpa[1111];
int checkit(int a){
    if (a==n) return 0;
    int &r=dpa[a];
    if (r!=-1) return r;
    int mx=h[a];
    r=maxn;
    FOR(i,a,min(next[a],n)) checkmin(r,mx+checkit(i+1)), checkmax(mx, h[i+1]);
    return r;

}


void gen(){
    n=7;
    REP(i,n){
        t[i]=(1+rand()%n);
        h[i]=rand()%1000;
    }
}

const int leaf=1<<18;
const int maxm=leaf<<1;
int treea[maxm], treeb[maxm];
int cnta[maxm];

inline int getm(int a, int b){if (a==-1) return b; if (b==-1) return a;if (h[a]!=h[b]) return h[a]<h[b]?b:a;  return a<b?b:a;}

void erasea(int x){
    if (--cnta[x]) return;
    int p=x+leaf;
    treea[p]=-1;
    while(p){
        int np=p>>1;
        treea[np]=max(treea[p],treea[p^1]);
        p=np;
    }
}
void inserta(int x){
    if (cnta[x]++) return;
    int p=x+leaf;
    treea[p]=x;
    while(p){
        int np=p>>1;
        treea[np]=max(treea[p],treea[p^1]);
        if (treea[np]!=x) return;
        p=np;
    }
}

void eraseb(int x){
    int p=x+leaf;
    treeb[p]=-1;
    while(p){
        int np=p>>1;
        treeb[np]=getm(treeb[p],treeb[p^1]);
        p=np;
    }
}
void insertb(int x){
    int p=x+leaf;
    treeb[p]=x;
    while(p){
        int np=p>>1;
        treeb[np]=getm(treeb[p],treeb[p^1]);
        if (treeb[np]!=x) return;
        p=np;
    }
}





int main(){
    int tn; cin>>tn;
    srand(2);
    REP(ti,tn){
    memset(dpa,-1,sizeof(dpa));
        cin>>n;
        REP(i,n) scanf("%d%d", t+i,h+i);
        gen();
        out(t,n);
        out(h,n);

        memset(vis,0,sizeof(vis));
        int qa=0, qe=0;

        memset(treea,-1,sizeof(treea));
        memset(treeb,-1,sizeof(treeb));
        memset(cnta,0,sizeof(cnta));

        int mid=0, pmid=0;
        for (int i=0, j=0; i<n; ++i){
            for (; j<n && !vis[t[j]]; ++j){
                vis[t[j]]=1;
                insertb(j);
                //while(qa<qe && h[q[qe-1]]<h[j]) --qe;
                //if (qa==qe){
                //    for (; pmid<j; ++pmid) qx.insert(h[pmid]);
                //    printf("updated %d to %d ( %d %d\n", i, j, h[i], h[j]);
                //}
                //q[qe++]=j;
            }
            next[i]=j;
            mx[i]=treeb[1];
            assert(mx[i]!=-1);

            while(pmid<mx[i]) inserta(h[pmid++]);
            if (pmid==i) inserta(h[pmid++]);
            prev[i]=treea[1];
            int val=h[i];
            FOR(k,i,mx[i]) checkmax(val,h[k]);
            assert(val==prev[i]);

            vis[t[i]]=0;
            //if (q[qa]==i) ++qa;
            eraseb(i);
            erasea(h[i]);
        }
        ll res=0;
        memset(dp,-1,sizeof(dp));
        res=go(0);
        printf("%Ld %d\n", res, checkit(0));
        assert(res==checkit(0));
        printf("Case %d: %Ld\n", ti+1, res);
    }
    return 0;
}



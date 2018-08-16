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


const int maxn=444444;
const int maxb=20;
int a[maxn], s[maxn], b[maxn], ns[maxn];
char buf[maxn];
int n;
int U;
int A[maxb][maxn];
int id[maxn];
int which[maxn];
ll res[maxn];
int F[maxn];

int cmp(int a, int b){if (s[a]!=s[b]) return s[a]<s[b]; return s[a+U]<s[b+U];}
     

void make_sa(){
    memcpy(s,a,sizeof(s));
    REP(i,n) b[i]=i;
    memset(ns,-1,sizeof(ns));
    for (U=1; 2*U<=n; U*=2){
        sort(b,b+n,cmp);
        int x=0;
        REP(i,n){
            if (i && cmp(b[i-1],b[i])) ++x;
            ns[b[i]]=x;
        }
        memcpy(s,ns,sizeof(ns));
    }
}

void make_lcp(){
    int h=0;
    memset(A,0x7f,sizeof(A));
    REP(i,n){
        if (s[i]){
            for (int j=b[s[i]-1]; a[j+h]==a[i+h]; ++h);
            A[0][s[i]-1]=h;
        }
        if (h) --h;
    }
    REP(i,maxb-1) REP(j,n) A[i+1][j]=min(A[i][j],A[i][j+(1<<i)]);
}

int lcp(int a, int b){
    if (b<a) swap(a,b);
    int x=0;
    for (; 2<<x<=b-a; ++x); 
    return min(A[x][a],A[x][b-(1<<x)]);
}


int getl(int p, int v){
    int x=p;
    for (int i=maxb-1; i>=0; --i) if (x-(1<<i)>=0 && A[i][x-(1<<i)]>=v) x-=1<<i;
    return x;
}
int getr(int p, int v){
    int x=p;
    for (int i=maxb-1; i>=0; --i) if (x+(1<<i)<n && A[i][x]>=v) x+=1<<i;
    return x;
}

int main(){
    int m, K; cin>>m>>K;
    n=0;
    REP(i,m){
        scanf(" %s", buf);
        int x=strlen(buf);
        REP(j,x) id[n]=i, a[n++]=buf[j]-'a'+1;
        if (K==1) res[i]=1ll*x*(x+1)/2;
        id[n]=-1;
        a[n++]=-1e9-i;
    }
    --n;

    if (K>1){
        make_sa();
        make_lcp();

        set<pii> x;
        int j=0;
        REP(i,n){
            for (; j<n && x.size()<K; ++j) if (id[b[j]]!=-1){
                int k=b[j];
                if (which[id[k]]>=i) x.erase(MP(which[id[k]],id[k]));
                x.insert(MP(j,id[k])), which[id[k]]=j;
            }
            if (x.size()==K) F[i]=j-1;
            else F[i]=n;
            if (id[b[i]]!=-1 && which[id[b[i]]]==i) x.erase(MP(i,id[b[i]]));
        }


        REP(i,n) if (id[b[i]]!=-1){
            int T=0, H=n, best=0;
            while(T<=H){
                int M=T+H>>1;
                int l=getl(i,M), r=getr(i,M);
                if (F[l]<=r) T=M+1, best=M;
                else H=M-1;
            }
            res[id[b[i]]]+=best;
        }
    }

    //REP(i,m) printf("%Ld ", res[i]); puts("");
    REP(i,m) printf("%I64d ", res[i]); puts("");
    return 0;
}



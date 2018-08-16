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
const int maxb=11;
const ll inf=2e9;
int dp[maxn][maxb];
ll dpb[maxn][maxb];
int have[2*maxb];
int is[10];


int c[maxn];
int n, m, k;
int na;


int go(int a, int b){
    if (b<0) return 0;
    if (a==0) return !b;
    int &r=dp[a][b];
    if (r!=-1) return r;
    r=0;
    REP(j,10) r+=go(a-1,b-is[j]);
    return r;
}
int get(int nm){ int x=0; while(nm) x+=is[nm%10], nm/=10; return x; }


int geta(int m, int u){
    if (!m) return 0;
    int res=0;
    int x, nm;
    x=get(m);
    nm=m;
    res+=x==u;
    int pos=0;
    while(nm){
        x-=is[nm%10];
        REP(j,nm%10) res+=go(pos,u-x-is[j]);
        ++pos;
        nm/=10;
    }
    if (!u) --res;
    return res;
}


ll gob(int p, int last){
    if (p==n) return 1;
    ll &r=dpb[p][last];
    if (r!=-1) return r;
    r=0;
    REP(i,maxb) if (c[p]^i!=last) r=min(inf,r+have[i]*gob(p+1,i));
    return r;
}

ll proc(int M, int p, int last){
    ll res=0;
    REP(i,maxb) if (c[p]^i!=last) res=min(inf,res+geta(M,i)*gob(p+1,i));
    return res;
}

void doit(int k, int p, int last){
    if (p==n) return;
    int T=1, H=m, best;
    while(T<=H){
        int M=(T+H)/2;
        int cnt=proc(M,p,last);
        if (cnt<k) T=M+1;
        else H=M-1, best=M;
    }
    if (p) printf(" ");
    printf("%d", best);
    //puts("");
    //printf("FUUU %d\n", geta(3,0));
    //printf("HAVE %Ld, previous: %Ld\n", proc(best,p,last), proc(best-1,p,last));
    doit(k-proc(best-1,p,last),p+1,get(best));
}

void checkit(int n, int m, int K){
    vector<vi> lst;
    lst.pb(vi());
    REP(i,n){
        vector<vi> nlst;
        REP(j,lst.size()){
            REP(k,m){
                int ok=0;
                if (!i) ok=1;
                else{
                    int u=get(k+1), v=get(lst[j].back());
                    if ((u!=v)^c[i]) ok=1;
                }
                if (ok) nlst.pb(lst[j]), nlst.back().pb(k+1);
            }
        }
        lst=nlst;
    }
    sort(ALL(lst));
    printf("<<< %d\n",lst.size());
    //REP(i,lst.size()) out(lst[i]);
    if (lst.size()<K) printf("-1\n");
    else out(lst[K-1]);
}


int main(){
    int tn; cin>>tn;
    is[4]=is[7]=1;

    REP(ti,tn){
        cin>>n>>m>>k;
        memset(dp,-1,sizeof(dp));
        memset(have,0,sizeof(have));
        REP(i,n-1) cin>>c[i+1];

        REP(i,maxb) have[i]=geta(m,i);
        memset(dpb,-1,sizeof(dpb));



        if (gob(0,maxb-1)-1<k) printf("-1\n");
        else doit(k,0,maxb-1), puts("");
        //checkit(n,m,k);
    }

    return 0;
}



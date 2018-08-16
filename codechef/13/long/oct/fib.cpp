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

int mod;
const int n=2;
const int maxn=5e4;


int pl[maxn];
int is[maxn];
int np;

int ub;

int g1[maxn], g2[maxn], ig1[maxn], ig2[maxn];
int phi1[maxn], phi2[maxn];
int iphi1[maxn], iphi2[maxn];
int sq5, isq5;

int faste(int a, int p){ int x=1; for (; p; p>>=1, a=1ll*a*a%mod) if (p&1) x=1ll*x*a%mod; return x; }
int inv(int a){return faste(a,mod-2);}

vector<pii> sq1;
vector<pii> lst;

int checkit(int v, int r, int m){
    if (v==0) return r==0;
    if (v==1) return r==1;
    int a=1, b=1;
    r-=3;

    while(a!=1 || b!=0){
        int c=(a+b)%m;
        b=a;
        a=c;
        if (a==v) return r==0;
        --r;
        if (r==-1) return 0;
    }
    return 1;
}

int check_fib(int pos, int x){
    int v1=1ll*phi1[pos%ub]*phi2[pos/ub]%mod;
    int v2=1ll*iphi1[pos%ub]*iphi2[pos/ub]%mod;
    int res=(mod+v1+(pos&1?v2:-v2))%mod;
    res=1ll*res*isq5%mod;
    //printf("for %d %d >> have %d\n",pos,x,res);
    return res==x;


    if (pos==0) return x==0;
    if (pos==1) return x==1;
    pos-=2;

    int a=1, b=1;
    while(a!=1 || b!=0){
        if (!pos--) return x==a;
        int c=(a+b)%mod;
        b=a;
        a=c;
    }
    return 0;
}


vector<pii> go_factor(int a){
    vector<pii> res;
    REP(i,np){
        if (pl[i]*pl[i]>a) break;
        int cnt=0;
        while(a%pl[i]==0) a/=pl[i], ++cnt;
        res.pb(MP(pl[i],cnt));
    }
    if (a>1) res.pb(MP(a,1));
    return res;
}

int find_gen(const vector<pii> &factor){
    FOR(i,2,mod){
        int fd=0;
        REP(j,factor.size()) if (faste(i,(mod-1)/factor[j].ST)==1){fd=1; break;}
        if (!fd){
            //int x=1;
            //set<int> seen;
            //REP(j,mod-2){
            //    assert(!seen.count(x));
            //    seen.insert(x);
            //    x=1ll*x*i%mod;
            //}
            return i;
        }
    }
    
    assert(0);
}


int getpos(vector<pii> &a, int u){
    vector<pii>::iterator it=lower_bound(ALL(a),MP(u,0));
    if (it==a.end() || it->ST!=u) return -1;
    return it-a.begin();
}

int sqrt_mod(int a){
    if (a==0) return 0;

    //REP(i,mod) if (1ll*i*i%mod==a) printf("cnd %d\n",i);
    REP(i,ub){
        int u=1ll*a*ig2[i]%mod*ig2[i]%mod;
        int tmp=getpos(sq1,u);
        if (tmp==-1) continue;
        tmp=sq1[tmp].ND;

        int res=1ll*g2[i]*g1[tmp]%mod;
        assert(1ll*res*res%mod==a);
        return res;
    }
    return -1;
}

int log_mod(int a, int b, int c){
    //printf("LOG MOD %d %d %d\n",a,b,c);
    //int x=1;
    //REP(i,mod-1){
    //    x=1ll*x*b%mod;
    //    if (x==a) printf("CAN %d\n",i);
    //}

    REP(i,ub){
        int x=1ll*a*iphi2[i]%mod;
        int tmp=getpos(lst,x);
        if (tmp==-1) continue;

        for (; tmp<lst.size() && lst[tmp].ST==x; ++tmp){
            if (check_fib(i*ub+lst[tmp].ND,c))return i*ub+lst[tmp].ND;
        }
        
    }

    return mod;
}

int disp(int m){
    int a=1, b=1;
    int nr=2;
    while(a!=1 || b!=0){
        ++nr;
        int c=(a+b)%m;
        b=a;
        a=c;
        printf("%d >> %d\n",nr,a);
    }
}
int get_fib(int m, int p){
    if (p==0) return 0;
    --p;
    int a=1, b=0;
    while(1){
        if (!p--) return a;
        int c=(a+b)%m;
        b=a;
        a=c;
    }
}





void proc(int *t1, int *t2, int g){
    t1[0]=1;
    REP(i,ub) t1[i+1]=1ll*t1[i]*g%mod;
    t2[0]=1;
    REP(i,ub) t2[i+1]=1ll*t2[i]*t1[ub]%mod;
}

int go(int p, int c){
    if (c==0) return 0;
    mod=p;
    vector<pii> factors=go_factor(mod-1);
    int g=find_gen(factors);

    ub=sqrt(mod)+1;

    proc(g1,g2,g);
    proc(ig1,ig2,inv(g));

    sq1.clear();
    REP(i,ub) sq1.pb(MP(1ll*g1[i]*g1[i]%mod,i));
    sort(ALL(sq1));



    sq5=sqrt_mod(5);
    assert(sq5!=-1);
    isq5=inv(sq5);

    int i2=(mod+1)/2;
    int phi=1ll*(1+sq5)*i2%mod;

    proc(phi1,phi2,phi);
    proc(iphi1,iphi2,inv(phi));

    lst.clear();
    REP(i,ub) lst.pb(MP(phi1[i],i));
    sort(ALL(lst));



    int tmp=5ll*c%mod*c%mod;
    int best=mod;

    for (int sgn=-1; sgn<=1; sgn+=2){
        int x=sqrt_mod((1ll*tmp+4*sgn+mod)%mod);
        if (x==-1) continue;

        REP(f,2){
            int v=(1ll*c*sq5+x)%mod*i2%mod;
            int res=log_mod(v,phi,c);
            best=min(best,res);
            x=mod-x;
        }
    }
    best=best==mod?-1:best;

    //printf("%d %d >> %d\n",p,c,best);
    //assert(checkit(c,best,mod));
    return best;
}

int checkprime(int x){return !(x!=1 && x!=4 && x!=9);}

void test(){
    int step=10;
    while(1){
        int x=pl[rand()%np];

        if (!checkprime(x%10)) continue;
        printf("%d\n",go(x,rand()%3?get_fib(x,rand()%x):rand()%x));
        puts("");
        --step;
    }
    exit(0);
}


int main(){
    srand(0);
    memset(is,1,sizeof(is));

    np=0;
    FOR(i,2,maxn) if (is[i]){
        for (ll j=1ll*i*i; j<maxn; j+=i) is[j]=0;
        pl[np++]=i;
    }

    //test();

    int tn; cin>>tn;
    REP(ti,tn){
        int p,c; scanf(" %d%d",&c,&p);
        int res=go(p,c);
        printf("%d\n",res);
    }

    return 0;
}


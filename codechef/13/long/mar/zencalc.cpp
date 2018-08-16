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

const int maxn=22222;
const int maxb=1<<12;
const int maxfact=55;


char buf[22];
int rmp[255];
const char *str="!^/*+-";
const ll MOD=1ll<<32;

int next[maxn], prev[maxn];
int cnt[maxn];
int type[maxn], val[maxn];
int done[maxn];
int par[maxn];

int tree[maxb];

int get(int a){int res=0; for (++a; a; a&=a-1) res+=tree[a]; return res;}
void update(int a, int v){for (++a; a<maxb; a+=a&-a) tree[a]+=v;}

int m;
priority_queue<int, vi, greater<int> > q1;
priority_queue<pii,vector<pii>, greater<pii> > q2,q3;
int fact[maxfact+10];

int root(int a){return par[a]==-1?a:par[a]=root(par[a]);}

ll bezout(ll u, ll v, ll ua, ll va, ll ub, ll vb, ll &ux, ll &vx){
    if (!v){ux=ua; vx=va; return u;}
    ll k=u/v;
    return bezout(v,u-k*v,ub,vb,ua-k*ub,va-k*vb,ux,vx);
}


void check(int a, ll b){
    ll na=a;
    if (na<0) na+=MOD;
    b=(MOD+b%MOD)%MOD;
    assert(na==b);
}

int mul(int a, int b){ 
    check(a*b,1ll*a*b);
    return a*b; 
}
int add(int a, int b){
    check(a+b,1ll*a+b);
    return a+b;
}
int sub(int a, int b){
    check(a-b,1ll*a-b);
    return a-b;
}

int faste(int a, ll p){
    int x=1;
    assert(p>=0);
    for (; p; a=mul(a,a), p>>=1) if (p&1) x=mul(a,x);
    return x;
}


ll div2(ll a, ll b){
    if (!a){
        return b&1?0:-(1ll<<31);
    }
    //1*a=k*MOD+x*b

    if (!b) throw "";
    ll u,v;
    ll d=bezout(MOD,b<0?-b:b,1,0,0,1,u,v);
    if (b<0) v=-v;
    if (a%d) throw "";
    v*=a/d;
    assert(d>0);
    ll K=MOD/d;
    ll WANT=-(1ll<<31);
    v+=(WANT-v)/K*K;

    //assert(fabs(WANT-v)<=K);
    while (v<WANT) v+=K;
    while (v-K>=WANT) v-=K;
    return v;
}

int doit(int p, ll a, ll b){
    int oa=a,ob=b;
    int res;
    int sgn=1;

    switch(type[p]){
        case 1:
            if (a<0){
                a=-a;
                sgn=a&1?-1:1;
            }
            res=sgn*fact[min((ll)maxfact-1,a)];
            break;
        case 2:
            res=faste(a,b<0?-b:b);
            if (b<0){
                int tmp=res;
                res=div2(1,res);
                assert(tmp*res==1);
            }
            break;
        case 3:
            res=div2(a,b);
            //printf("%d %d >> %d\n",oa,ob,res);
            assert(res*ob==oa);
            break;
        case 4:
            res=mul(oa,ob);
            break;
        case 5:
            res=add(oa,ob);
            break;
        case 6:
            res=sub(oa,ob);
            break;
        default:
            throw "";
            //assert(0);
    }
    printf("%d %c %d %d %d\n",get(p)-1,str[type[p]-1],oa,ob,res);
    return res;
}

void go(int a, int b, int res){
    int diff=0;
    update(a+1,-1);
    if (next[a]!=b) assert(next[next[a]]==b), update(a+1,-1), diff=-1;

    type[a]=0; val[a]=res;
    next[a]=next[b];
    prev[next[a]]=a;


    int x=prev[a];
    x=root(x);
    assert(a==root(a));
    par[a]=x;
    if (x){
        cnt[x]+=cnt[a]+diff;
        if (type[x]==1) q1.push(x);
        else if (cnt[x]>=3) q3.push(MP(type[x],x));
        else if (cnt[x]==2) q2.push(MP(type[x],x));
    }
}


int main(){
    REP(i,strlen(str)) rmp[str[i]]=i+1;

    fact[0]=1;
    REP(i,maxfact-1) fact[i+1]=(i+1)*fact[i];

    int tn; cin>>tn;
    REP(ti,tn){
        int n; scanf(" %d",&n);
        int last=0;
        m=1;
        while(q1.size()) q1.pop();
        while(q2.size()) q2.pop();
        while(q3.size()) q3.pop();

        memset(par,-1,sizeof(par));
        memset(cnt,0,sizeof(cnt));
        REP(i,n+1){
            if (i==n) buf[0]='!', buf[1]=0;
            else scanf(" %s",buf);

            type[m]=0;

            if (strlen(buf)>1 || (buf[0]>='0' && buf[0]<='9')) sscanf(buf,"%d",val+m), ++cnt[last];
            else type[m]=rmp[buf[0]];

            next[m-1]=m;
            prev[m]=m-1;
            par[m]=last;
            if (type[m]){
                if (last){
                    if (type[last]==1 && cnt[last]) q1.push(last);
                    else if (cnt[last]>=3) q3.push(MP(type[last],last));
                    else if (cnt[last]==2) q2.push(MP(type[last],last));
                }
                last=m;
                par[m]=-1;
            }
            ++m;
        }
        memset(tree,0,sizeof(tree));
        REP(i,m) update(i,1);

        try{
            memset(done,0,sizeof(done));
            int step=0;
            while(1){
                assert(++step<maxn);
                while(q2.size() && done[q2.top().ND]) q2.pop();
                while(q3.size() && done[q3.top().ND]) q3.pop();

                if (next[next[0]]==m-1){
                    if (type[next[0]]) throw "";
                    puts("OK"); break;
                }
                if (q1.size()){
                    int p=q1.top(); q1.pop();
                    int a=next[p];
                    assert(type[p]==1);
                    assert(!type[a]);
                    int res=doit(p,val[a],-1);
                    go(p,a,res);
                }else if (q3.size()||q2.size()){
                    int p,a,b;
                    if (q3.size()) p=q3.top().ND, q3.pop();
                    else p=q2.top().ND, q2.pop();

                    done[p]=1; a=next[p]; b=next[a];
                    //assert(type[p]>1 && type[p]<=6);
                    assert(!type[a]);
                    assert(!type[b]);
                    int res=doit(p,val[a],val[b]);
                    go(p,b,res);
                }else throw "";
            }
        }catch(char const *s){

            puts("NOT OK");
        }
    }
    return 0;
}


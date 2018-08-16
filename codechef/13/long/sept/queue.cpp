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
inline int low_bit(int n){return (n^n-2)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}


const int maxb=20;
const int maxn=1<<maxb;
const int mod=1e9+7;

char s[maxn];
char qq[maxn];
int nq;
int n;
char buf[11];
const int oo=1e9;



int rmp[2*maxn], tmp[maxn];
int A[2*maxn];
int NB;
int X;
int V;

int nA[maxn];
int cnt[maxn];
int val[maxn];
bool b[maxn];
int bb[maxn];


//int lcp[maxb][maxn];



int lcp[maxn];

int cmp(int a, int b){
    int u=rmp[a], v=rmp[b];
    if (u!=v) return u<v;
    u=X+a<n?rmp[a+X]:-oo;
    v=X+b<n?rmp[b+X]:-oo;
    return u<v;
}


void rsort(int *a, int n){
    memset(cnt,0,sizeof(int)*V);
    REP(i,n) val[i]=(a[i]+X<n?1+rmp[a[i]+X]:0), ++cnt[val[i]];
    //REP(i,n) val[i]=rmp[a[i]+X], ++cnt[val[i]];
    REP(i,V) cnt[i+1]+=cnt[i];
    for (int i=n-1; i>=0; --i) nA[--cnt[val[i]]]=a[i];

    memset(cnt,0,sizeof(int)*V);
    REP(i,n) val[i]=rmp[nA[i]], ++cnt[val[i]];
    REP(i,V) cnt[i+1]+=cnt[i];
    for (int i=n-1; i>=0; --i) a[--cnt[val[i]]]=nA[i];
}


void proc(){
    int oldn=n;
    s[n++]='a'-1;
    s[n++]='z'+2;
    V=128;

    REP(i,n) rmp[i]=s[i];

    memset(bb,0,sizeof(bb));
    bb[n]=1;

    REP(i,n) A[i]=i;
    for (int b=1; b<maxb+1; ++b){
        X=1<<(b-1);
        for (int i=0,j=0; j<=n; ++j) if (bb[j]) sort(A+i,A+j,cmp), i=j;
        //rsort(A,n);
        //sort(A,A+n,cmp);
        tmp[A[0]]=1;
        REP(i,n-1){
            tmp[A[i+1]]=tmp[A[i]];
            if (cmp(A[i],A[i+1])) bb[i+1]=1, ++tmp[A[i+1]];
        }
        V=tmp[A[n-1]]+2;
        memcpy(rmp,tmp,sizeof(tmp));
    }
    REP(i,n) --rmp[i];

    int u=0;
    A[n]=n-1;
    for (NB=0; 1<<NB<n; ++NB);
    FOR(i,n,1<<NB) A[i]=n-1;

    REP(i,n-2){
        int j=A[rmp[i]+1];

        if (i==j){printf("suffix array fail rofl: -1 on %d %d xx %d\n",i,j,n); exit(0);}

        for (; s[i+u]==s[j+u]; ++u);
        lcp[rmp[i]]=u;
        if (u) --u;
    }
    //for (int i=1; i<maxb; ++i) REP(j,n) lcp[i][j]=min(lcp[i-1][j],(j+(1<<i-1)>=n-1?0:lcp[i-1][j+(1<<i-1)]));
}
 

int f[maxn];
int xlcp[2*maxn];
int p[maxn],q[maxn];
bool scmp(int x,int y){ return f[x]<f[y]; }
struct suffixarray{
    int __lcp(int i,int j){
        if(i>j)swap(i,j);
        int res=n;
        for(i+=n,j+=n-1;i<=j;i=i+1>>1,j=j-1>>1)
            res=min(res,min(xlcp[i],xlcp[j]));
        return res;
    }
    void setlcp(int i,int v){ for(i+=n;xlcp[i]>v;i/=2)xlcp[i]=v; }
    void suff_sort(){
        REP(i,n)b[i]=0,p[i]=i; b[n]=true;
        for(int i,j,x,h=0;h<n;){
            for(i=j=0;j<=n;++j)if(b[j])sort(p+i,p+j,scmp),i=j;
            for(i=0,j=1;j<n;++i,++j)b[j]|=f[p[i]]!=f[p[j]];
            for(h=h?h*2:1,i=x=0;i<n;f[j]=x+=b[i++])if((j=p[i]-h)<0)j+=n;
        }
    }
    void suff_sort_withlcp(){
        memset(b,0,sizeof(b));
        REP(i,n)b[i]=0,p[i]=i,xlcp[i+1]=xlcp[i+n]=n; b[n]=true;
        for(int i,j,x,y,h=0;h<n;){
            for(i=j=0;j<=n;++j)if(b[j])sort(p+i,p+j,scmp),i=j;
            REP(k,n)q[p[k]]=k;
            for(i=0,j=1;j<n;++i,++j)
                if(!b[j] && f[p[i]]!=f[p[j]])
                    b[j]=true,x=p[i]+h,y=p[j]+h,
                        setlcp(i,h?h+__lcp(q[x<n?x:x-n],q[y<n?y:y-n]):0);
            for(h=h?h*2:1,i=x=0;i<n;f[j]=x+=b[i++])if((j=p[i]-h)<0)j+=n;
        }
        REP(i,n) lcp[i]=__lcp(i,i+1);
        memcpy(rmp,f,sizeof(f));
    }
};






int addl[maxn];
int have, add;
int N;
int lt[maxn], rt[maxn];

int inx[maxn];
int outx[maxn];
int routx[maxn];

int ub[maxn];
int tb[2*maxn];
int rmql[2*maxn], rmqr[2*maxn];



int dd[maxn];

void update_min(int *tb, int a, int v){
    a+=maxn;
    while(a) tb[a]=min(tb[a],v), a>>=1;
}

void update_max(int *tb, int a, int v){
    a+=maxn;
    while(a) tb[a]=max(tb[a],v), a>>=1;
}

int query_tb(int a, int b){
    a+=maxn; b+=maxn;
    int res=max(tb[a],tb[b]);
    for (; a+1<b; a>>=1, b>>=1){
        if (!(a&1) && res<tb[a^1]) res=tb[a^1];
        if ((b&1) &&  res<tb[b^1]) res=tb[b^1];
    }
    return res;
}
int query_tb2(int a, int b){
    a+=maxn; b+=maxn;
    int res=min(tb[a],tb[b]);
    for (; a+1<b; a>>=1, b>>=1){
        //printf("query %d %d %d \n",a,b,res);
        if (!(a&1) && res>tb[a^1]) res=tb[a^1];
        if ((b&1) &&  res>tb[b^1]) res=tb[b^1];
    }
    return res;
}

void find_lcp_range(int a, int l, int &ll, int &rr){
    ll=rmp[a]; rr=rmp[a];
    assert(0);
    //for (int i=maxb-1; i>=0; --i) if (ll-(1<<i)>=0 && lcp[i][ll-(1<<i)]>=l) ll-=1<<i;
    //for (int i=maxb-1; i>=0; --i) if (rr+(1<<i)<=n && lcp[i][rr]>=l) rr+=1<<i;
}

int checkit2(int p, int l, int np){
    int ll,rr;
    find_lcp_range(p,l,ll,rr);

    //printf("at %d, lcp range with length %d >> %d %d\n",rmp[p],l,ll,rr);
    int x=query_tb2(ll,rr);//time at which 
    //printf("get min at pos %d\n",x);
    return (x<n && np-x>=l);
}

int checkit(int a, int t){
    int l=rt[t+1]-a;

    int ll,rr;
    find_lcp_range(a,l,ll,rr);
    //printf(">> with length %d >>\n",l);
    //printf("%dxx %d >>  %d >> %d %d\n",a,rmp[a],t,ll,rr);

    int x=query_tb(ll,rr);

    //printf("fuuu %d >> %d\n",x,t+1);
    return x==-1 || outx[x]<=t;
}





int eval_diff(int e, int u, int ll){
    if (u>=n) return 0;
    if (ll==0) return 1;
    return inx[u+ll-1]<outx[e];
}

void update_diff(int e, int u, int ll, int &r){
    if (u>=n) return;
    r=max(r,min(ll,rt[outx[e]]-u));
}


int get_diff(int p){

    int ANS=0;
    int lx=oo;
    int b; 

    int *rmqq=rmqr;
    for (int a=rmp[p]+maxn;a;a>>=1){
        if (a&1){
            //look left if fail
            if (eval_diff(p,tb[a^1],min(lx,rmqq[a^1]))){
                for (b=a^1; b<maxn;){
                    b<<=1;
                    if (eval_diff(p,tb[b+1],min(lx,rmqq[b+1]))) ++b;
                    else update_diff(p,tb[b+1],lx=min(lx,rmqq[b+1]),ANS);
                }
                lx=min(lx,rmqq[b]);
                update_diff(p,tb[b],lx,ANS);
                break;
            }
            lx=min(lx,rmqq[a^1]);
            update_diff(p,tb[a^1],lx,ANS);
        }
    }

    rmqq=rmql;
    lx=oo;
    for (int a=rmp[p]+maxn;a;a>>=1){
        if (!(a&1)){
            //look left if fail
            if (eval_diff(p,tb[a^1],min(lx,rmqq[a^1]))){
                for (b=a^1; b<maxn;){
                    b<<=1;
                    if (eval_diff(p,tb[b],min(lx,rmqq[b])));
                    else update_diff(p,tb[b],lx=min(lx,rmqq[b]),ANS), ++b;
                }
                lx=min(lx,rmqq[b]);
                update_diff(p,tb[b],lx,ANS);
                break;
            }
            lx=min(lx,rmqq[a^1]);
            update_diff(p,tb[a^1],lx,ANS);
        }

    }
    return ANS;
}

int slow_get_diff(int p){
    int np=rt[outx[p]];
    int l=np-p;
    int T=1, H=l-1;
    int best=0;
    //maybe can go lg n

    while(T<=H){
        int M=T+H>>1;
        if (checkit2(p,M,np)) best=M, T=M+1;
        else H=M-1;
    }
    return best;
}


int eval(int e, int u, int ll){
    if (u==-1) return 0;
    return inx[e+ll]<=outx[u];
}


void update_conflict(int a, int b, int ll, int &r){
    if (b==-1) return;
    int tx=min(outx[b],inx[a+ll]);
    r=max(r,tx);
}

int get_active(int p){

    //goal: find last elem with conflict
    int ANS=inx[p];
    int lx=oo;
    int b; 

    int *rmqq=rmqr;
    for (int a=rmp[p]+maxn;a;a>>=1){
        if (a&1){
            //look left if fail
            if (eval(p,tb[a^1],min(lx,rmqq[a^1]))){
                for (b=a^1; b<maxn;){
                    b<<=1;
                    if (eval(p,tb[b+1],min(lx,rmqq[b+1]))) ++b;
                    else update_conflict(p,tb[b+1],lx=min(lx,rmqq[b+1]),ANS);

                }
                lx=min(lx,rmqq[b]);
                update_conflict(p,tb[b],lx,ANS);
                break;
            }
            lx=min(lx,rmqq[a^1]);
            update_conflict(p,tb[a^1],lx,ANS);
        }
    }

    rmqq=rmql;
    lx=oo;
    for (int a=rmp[p]+maxn;a;a>>=1){
        if (!(a&1)){
            //look left if fail
            if (eval(p,tb[a^1],min(lx,rmqq[a^1]))){
                for (b=a^1; b<maxn;){
                    b<<=1;
                    if (eval(p,tb[b],min(lx,rmqq[b])));
                    else update_conflict(p,tb[b],lx=min(lx,rmqq[b]),ANS), ++b;
                }
                lx=min(lx,rmqq[b]);
                update_conflict(p,tb[b],lx,ANS);
                break;
            }
            lx=min(lx,rmqq[a^1]);
            update_conflict(p,tb[a^1],lx,ANS);
        }

    }
    return ANS;
}

int slow_get_active(int p, int t){

    int T=t, H=outx[p]==-1?nq-1:outx[p]-1;
    int best=nq;
    //printf("RANGE %d %d \n",T,H);

    while(T<=H){
        int M=T+H>>1;
        if (checkit(p,M)) H=M-1, best=M;
        else T=M+1;
    }
    return best;
}

int go(){
    ub[0]=-1;
    ub[1]=0;
    FOR(i,1,n) ub[i]=ub[i>>1]+1;

    int xx=0;
    REP(i,n) outx[i]=nq;
    REP(i,nq) if (qq[i]==-1) outx[xx++]=i;
    xx=0;
    REP(i,nq) if (qq[i]!=-1) inx[xx++]=i;
    inx[xx]=nq;

    memset(rmql,0x7f,sizeof(rmql));
    memset(rmqr,0x7f,sizeof(rmqr));
    REP(i,n-1) update_min(rmqr,i,lcp[i]);
    REP(i,n) update_min(rmql,i+1,lcp[i]);


    int ll=0, rr=0;
    REP(i,nq){
        lt[i]=ll; rt[i]=rr;
        if (qq[i]==-1) ++ll;
        else ++rr;
    }
    lt[nq]=ll; rt[nq]=rr;

    //cout<<s<<endl;
    // REP(i,nq){
    //    printf("%d: ",i);
    //    for (int j=lt[i+1]; j<rt[i+1]; ++j) printf("%c",s[j]);
    //    puts("");
    //}
    //REP(i,n) cout<<i<<' '<<s+A[i]<<endl;
    //out(lt,nq);
    //out(rt,nq);
    //out(inx,n);
    //out(outx,n);

    memset(dd,-1,sizeof(dd));
    memset(tb,0x7f,sizeof(tb));

    //printf("1\n");
    REPV(i,nq){
        if (qq[i]!=-1){
            if (outx[rt[i]]!=nq){
                //printf("%d %d\n",i,rt[i]);
                dd[outx[rt[i]]]=get_diff(rt[i]);
                //printf("for %d >> %d %d\n",i,dd[outx[rt[i]]],slow_get_diff(rt[i]));
                //assert(dd[outx[rt[i]]]==slow_get_diff(rt[i]));
                //printf("when %s disappear, %d of its substr are still there\n",s+rt[i],dd[outx[rt[i]]]);
            }
            //printf("adding %s %d %d\n",s+rt[i],rmp[rt[i]],rt[i]);
            update_min(tb,rmp[rt[i]],rt[i]);
        }
    }

    //printf("2\n");
    memset(tb,-1,sizeof(tb));
    REP(i,nq){
        //puts("");
        if (qq[i]!=-1){
            assert(dd[i]==-1);
            dd[i]=get_active(rt[i]);
            //assert(dd[i]==slow_get_active(rt[i],i));
            //printf("string at pos %s will lead at %d\n",s+rt[i],dd[i]);
            update_max(tb,rmp[rt[i]],rt[i]);
        }
    }

    int res=0;

    memset(addl,0,sizeof(addl));
    have=0;
    add=0;

    N=0;
    vi tt;

    REP(i,nq){
        if (qq[i]==-1){
            --add;
            int df=rt[i]-lt[i]-dd[i];
            //printf(">>> removing %d xx %d\n",df,add);
            have=(have+-df+mod)%mod;

        }else ++addl[dd[i]];


        add+=addl[i];
        if (qq[i]!=-1) have=(have+add)%mod;
        //printf("%s >> %d\n",s+lt[i],add);

        res=(res+have)%mod;


        tt.pb(have);
        //puts("");

    }

    //out(tt);
    //cout<<s<<endl;
    //REP(i,n) cout<<i<<' '<<s+A[i]<<endl;
    //REP(i,nq){ printf("%c >> %d\n",qq[i],tt[i]); }



    return res;

}


int eval(string s){
    set<string> tb;
    REP(i,s.size()){
        string tmp;
        for (int j=i; j<s.size(); ++j){
            tmp+=s[j];
            tb.insert(tmp);
        }
    }
    return tb.size();
}

int stupid(){
    int l=0, r=0;
    int res=0;

    vi tt;
    REP(i,nq){
        if (qq[i]==-1) ++l;
        else ++r;
        string ss;
        for (int j=l; j<r; ++j) ss+=s[j];

        int xx=eval(ss);
        tt.pb(xx);
        res+=xx;
    }
    //out(tt);

    return res;
}


void gen(){
    nq=1e2;
    int nx=0;
    int use=1;
    int sz=5;
    REP(i,nq){
        int x;
        while(1){
            x=rand()%3==0 && use;
            if (x==0 || nx>1) break;
        }
        if (x==0) qq[i]=s[n++]=rand()%sz+'a', ++nx;
        else qq[i]=-1, --nx;
        //printf(">> %d\n",qq[i]);
    }

    //puts("");

}

int main(){
    srand(0);
    int test=0;
    int check=0;

    int res;
start:
    n=0;
    if (!test){
        cin>>nq;
        REP(i,nq){
            scanf("%s",buf);
            if (buf[0]=='+'){
                char x;
                scanf(" %c",&x);
                s[n++]=x;
                qq[i]=x;
            }else qq[i]=-1;
        }
    }else gen();


    //suffixarray sa;
    //REP(i,n) f[i]=s[i];
    //f[n]=0;
    //f[n++]=-1;
    //f[n++]=2000;
    //sa.suff_sort_withlcp();
    //n-=2;
    //out(f,10);

    //cout<<s<<endl;
    //REP(i,nq) printf("%d ",qq[i]); puts("");
    //REP(i,nq){
    //    if (qq[i]==-1) printf("-\n");
    //    else printf("+ %c\n",qq[i]);
    //}

    proc();



    res=go();

    if (check){
        //puts("====");
        //puts("====");
        //puts("====");
        int ans=stupid();

        //cout<<s<<endl;
        //REP(i,nq) printf("%d ",qq[i]); puts("");
        //REP(i,nq){
        //    if (qq[i]==-1) printf("-\n");
        //    else printf("+ %c\n",qq[i]);
        //}
        //REP(i,nq){
        //    printf("%d: ",i);
        //    for (int j=lt[i+1]; j<rt[i+1]; ++j) printf("%c",s[j]);
        //    puts("");
        //}


        printf("%d %d\n",res,ans);
        assert(res==ans);
        //puts("");
        //puts("");
        if (test) goto start;
    }else printf("%d\n",res);


    return 0;
}



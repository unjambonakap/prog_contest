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
int lcp[maxb][maxn];
int A[2*maxn];
int NB;
int X;
int V;
char S[maxn];
int pos[maxn];

int nA[maxn];
int cnt[maxn];
int val[maxn];
int px[maxn];


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

int can(int a, int na){ return px[a+na]<na; }

void proc(){
    int oldn=n;
    s[n++]='a'-1;
    s[n++]='z'+2;
    V=256;

    REP(i,n) rmp[i]=s[i];

    for (int b=1; b<maxb+1; ++b){
        REP(i,n) A[i]=i;
        X=1<<(b-1);
        //rsort(A,n);
        sort(A,A+n,cmp);
        tmp[A[0]]=1;
        REP(i,n-1){
            tmp[A[i+1]]=tmp[A[i]];
            if (cmp(A[i],A[i+1])) ++tmp[A[i+1]];
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

        if (i==j){printf("-1 on %d %d xx %d\n",i,j,n); exit(0);}

        for (; s[i+u]==s[j+u]; ++u);
        lcp[0][rmp[i]]=u;
        if (u) --u;
    }
    for (int i=1; i<maxb; ++i) REP(j,n) lcp[i][j]=min(lcp[i-1][j],(j+(1<<i-1)>=n-1?0:lcp[i-1][j+(1<<i-1)]));
}
 

struct cmp2{ bool operator()(int a, int b)const{return rmp[a]<rmp[b];} };


int get_lcp(int a, int b){
    a=rmp[a]; b=rmp[b];
    assert(a<b);
    int res=oo;
    for (int i=maxb-1; i>=0; --i) if (a+(1<<i)<=b) res=min(res,lcp[i][a]), a+=1<<i;
    return res;
}

int addl[maxn];
int rmq[maxb][maxn];
int have, add;
int N;

typedef set<int,cmp2>::iterator sit;

void remove_adj(int a, int b){
    //b starts str
    int u=get_lcp(a,b);

    int st=max(a,b);
    printf("REM %d %d %d, then add %d\n",a,b,u,min(u,N-st));
    if (N-st<u) --addl[st+u], ++add;//have not diverged >>
    have+=min(u,N-st);
}

void add_adj(int a, int b){
    //b now after a
    int u=get_lcp(a,b);


    int st=max(a,b);
    printf("ADDING %d %d %d then rem %d\n",a,b,u,min(u,N-st));
    if (N-st<u) ++addl[st+u], --add;//have not diverged >>
    have-=min(u,N-st);
}

int go(){
    set<int,cmp2> sl;


    int xx=0;
    REP(i,n) rmp[0][i]=oo;
    REP(i,nq) if (qq[i]==-1) rmq[0][xx++]=i;
    for (int i=1; i<maxb; ++i) REP(j,n) rmq[i][j]=min(rmq[i-1][j],j+(1<<i)>=n?oo:rmq[i-1][j+(1<<i)]);

    
    int res=0;
    int nrem=0;

    memset(addl,0,sizeof(addl));
    have=0;
    add=0;

    N=0;
    vi tt;
    REP(i,nq){
        if (qq[i]==-1){
            sit it=sl.find(nrem);
            sit b;
            int l=-1,r=-1;

            if (it!=sl.begin()){
                b=it; --b;
                l=*b;
            }
            b=it; ++b;
            if (b!=sl.end()) r=*b;


            if (l!=-1) remove_adj(l,nrem);
            if (r!=-1) remove_adj(nrem,r);
            if (l!=-1 && r!=-1) add_adj(l,r);

            have-=N-nrem;
            --add;
            sl.erase(it);

            ++nrem;
        }else{

            add+=addl[N];
            printf("UUU %d %d %d\n",addl[N],add,N);
            have=(have+add)%mod;
            int x=N;
            sit it=sl.lower_bound(x);
            sit b;

            int l=-1, r=-1;
            if (it!=sl.end()) r=*it;
            b=it; 
            if (it!=sl.begin()) l=*--b;

            ++N;
            printf(">>>> %d %d %d\n",x,l,r);
            cout<<s+x<<endl;
            cout<<s+l<<endl;
            cout<<s+r<<endl;
            if (l!=-1 && r!=-1) remove_adj(l,r);
            if (l!=-1) add_adj(l,x);
            if (r!=-1) add_adj(x,r);

            ++have;
            ++add;
            it=sl.insert(x).ST;

        }


        tt.pb(have);
        res=(res+have)%mod;
        puts("");
        if (have==114) break;

    }
    out(tt);
    cout<<s<<endl;
    REP(i,n) cout<<i<<' '<<s+A[i]<<endl;
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
    out(tt);

    return res;
}


void gen(){
    nq=25;
    int nx=0;
    REP(i,nq){
        int x;
        while(1){
            x=rand()%5==0;
            if (x==0 || nx>1) break;
        }
        if (x==0) qq[i]=s[n++]=rand()%26+'a';
        else qq[i]=-1;
        //printf(">> %d\n",qq[i]);
    }

    //puts("");

}

int main(){
    srand(0);

    int test=0;
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

    proc();
    res=go();

    if (test){
        int ans=stupid();
        printf("%d %d\n",res,ans);
        cout<<s<<endl;
        REP(i,nq) printf("%d ",qq[i]); puts("");
        REP(i,nq){
            if (qq[i]==-1) printf("-\n");
            else printf("+ %c\n",qq[i]);
        }
        assert(res==ans);
        puts("");
        puts("");
        goto start;
    }else printf("%d\n",res);


    return 0;
}



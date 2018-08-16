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

const int maxn=111111;
const int maxm=222222;
const ll inf=1e9;
const double ths=2;


int last[maxn], to[maxm], prev[maxm], ne;
int rlast[maxn], rto[maxm], rprev[maxm], nre;
int on[maxn];
int vis[maxn];
int vis2[maxn];
int step;
int n, m;

int rem[maxn], la[maxn], lb[maxn], na, nb;
int ord[maxn];
int q[maxn];
int tx;

int cmp(int a, int b){return ord[a]<ord[b];}
struct cmpa{ bool operator()(int a, int b){return ord[a]<ord[b];}};
struct cmpb{ bool operator()(int a, int b){return ord[a]>ord[b];}};

int adde(int a, int b){prev[ne]=last[a]; last[a]=ne; to[ne]=b; ++ne;}
int addre(int a, int b){rprev[nre]=rlast[b]; rlast[b]=nre; rto[nre]=a; ++nre;}

void dfs(int a, vi &lst){
    if (vis[a]==step) return;
    vis[a]=step;
    for (int i=last[a]; i!=-1; i=prev[i]) dfs(to[i], lst);
    lst.pb(a);
}


void dfsa(int a){
    for (int i=on[a]; i!=-1; i=prev[i]){
        int b=to[i];
        if (ord[b]<tx && vis[b]!=step) vis[b]=step, on[b]=last[b], la[na++]=b, dfsa(b);
    }
}
void dfsb(int a){
    for (int i=on[a]; i!=-1; i=rprev[i]){
        int b=rto[i];
        if (ord[b]>tx && vis[b]!=step) vis[b]=step, on[b]=rlast[b], lb[nb++]=b, dfsb(b);
    }
}

void checkit(){
    REP(i,n) for (int j=last[i+1]; j!=-1; j=prev[j]){
        if (ord[i+1]>=ord[to[j]]) printf("fail on %d %d >> %d %d\n", i+1, to[j], ord[i+1], ord[to[j]]);
        assert(ord[i+1]<ord[to[j]]);
    }

}

void go(int u, int v){//adde u->v
    priority_queue<int,vi,cmpb> qf;
    priority_queue<int,vi,cmpa> qb;
    ++step; 
    na=nb=0;

    tx=ord[u];
    vis[v]=vis[u]=step;
    la[na++]=v; lb[nb++]=u;
    on[v]=last[v];
    on[u]=rlast[u];
    out(ord+1,n);
    if (on[v]!=-1) qf.push(v);
    if (on[u]!=-1) qb.push(u);
    while(1){
        if (qf.empty()||qb.empty()) break;
        int a=qf.top(), b=qb.top();
        printf("picking %d %d\n", a, b);
        if (ord[a]<ord[b]){
            int c=to[on[a]], d=rto[on[b]];
            on[a]=prev[on[a]];
            on[b]=rprev[on[b]];

            if (on[a]==-1) qf.pop();
            if (on[b]==-1) qb.pop();
            if (vis[c]!=step){
                la[na++]=c;
                vis[c]=step;
                on[c]=last[c];
                if (on[c]!=-1) qf.push(c);
            }if (vis[d]!=step){
                lb[nb++]=d;
                vis[d]=step;
                on[d]=rlast[d];
                checkmin(tx,ord[d]);
                if (on[d]!=-1) qb.push(d);
            }
        }else break;
    }
    while(qf.size()){
        dfsa(qf.top()), qf.pop();
    }
    while(qb.size()){
        printf("XXXXXXXX %d\n", qb.top());
        dfsb(qb.top()), qb.pop();
    }
    printf("xx xhave %d %d\n", na, nb);
    out(la,na);
    out(lb,nb);
    out(ord+1,n);
}


int main(){
    int tn; cin>>tn;
    //bench();
    REP(ti,tn){
        ne=nre=0;
        memset(last,-1,sizeof(last));
        memset(rlast,-1,sizeof(rlast));
        cin>>n>>m;
        REP(i,m){int a, b; scanf("%d%d", &a,&b); adde(a,b); addre(a,b);}
        step=1; memset(vis,0,sizeof(vis));

        vi lst;
        REP(i,n) dfs(i+1, lst);

        puts("");

        out(lst);
        REP(i,lst.size()) ord[lst[i]]=lst.size()-i;
        cerr<<ti<<endl;
        if (ti>1)break;
        printf("%d %d\n", n, m);
        out(ord+1,n);


        int a, b, c;
        int sw=0;
        int cnt=0;
        ll sum=0;
        while(scanf("%d%d%d", &a,&b,&c), a|b|c){
            ++cnt;

            //if (ti!=6)continue;
            //if (ti==6 && cnt%100==0){
            //    cerr<<cnt<<endl;
            //    fprintf(stderr, "%d %lf\n", ne, 1.*sum/cnt/sqrt(cnt));
            //}
            if (a){
                if (sw) swap(b,c);
                if (ord[b]>=ord[c]){
                    printf("adding edge %d %d\n", b, c);
                    //fprintf(stderr, "a\n");
                    go(b,c);
                    //fprintf(stderr, "b\n");
                    sum+=na+nb;


                    sort(la,la+na,cmp);
                    sort(lb,lb+nb,cmp);

                    //REP(i,la.size()-1) assert(ord[la[i]]<ord[la[i+1]]);
                    //REP(i,lb.size()-1) assert(ord[lb[i]]<ord[lb[i+1]]);
                    int nrem=0;

                    int i, j;
                    for (i=j=0; i<na&&j<nb;){
                        if (ord[la[i]]<ord[lb[j]]) rem[nrem++]=ord[la[i++]];
                        else rem[nrem++]=ord[lb[j++]];
                    }
                    for (; i<na; ++i) rem[nrem++]=ord[la[i]];
                    for (; j<nb; ++j) rem[nrem++]=ord[lb[j]];
                    
                    out(lb,nb);
                    REP(i,nb) ord[lb[i]]=rem[i];
                    REP(i,na) ord[la[i]]=rem[i+nb];
                    out(ord+1,n);
                }
                adde(b,c); addre(b,c);
                checkit();
            }else{
                if (ord[b]<ord[c]) puts("YES");
                else puts("NO"), sw^=1;
            }
        }
    }
    return 0;
}




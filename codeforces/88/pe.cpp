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
const int maxm=maxn*20;
vi e[maxn];
int n;
int vis[maxn], par[maxn];
int d[maxn];
int type[maxn];
vi cycle;
int A[maxn];
int skip[maxn];

int cyclePos[maxn];


struct segTree{
    int T, H;
    segTree *l,*r;
    int val, sw;
    void init(int T, int H);
    int getv(){return sw?H-T-val:val;}

    int query(int a, int b){
        if (b<=T || a>=H) return 0;

        if (T>=a && H<=b) return getv();
        if (sw){ val=H-T-val; sw=0; l->sw^=1, r->sw^=1; }
        return l->query(a,b)+r->query(a,b);
    }
    void update(int a, int b){
        assert(a<=b);
        if (b<=T || a>=H) return;
        if (T>=a && H<=b){sw^=1; return; }

        if (sw){ val=H-T-val; sw=0; l->sw^=1, r->sw^=1; }
        l->update(a,b);
        r->update(a,b);
        val=l->getv()+r->getv();
    }
};


segTree tbl[maxm];
int rmp[maxn];
int pos;


int getseg(){
    assert(pos<maxm);
    return pos++;
}

void segTree::init(int _T, int _H){
    l=r=0; val=0; sw=0;
    T=_T; H=_H;
    if (T+1==H) return;
    l=tbl+getseg(); r=tbl+getseg();
    int M=(T+H)/2;
    l->init(T,M);
    r->init(M,H);
}


int dfs(int a, int p){
    par[a]=p;
    if (vis[a]){cycle.pb(a); while(p!=a) cycle.pb(p), p=par[p]; cycle.pb(a); return 1;}
    vis[a]=1;
    REP(i,e[a].size()) if (e[a][i]!=p && dfs(e[a][i],a)) return 1;
    return 0;
}

void dfsb(int a, int p){
    A[a]=1;
    par[a]=p;
    d[a]=p==-1?0:d[p]+1;

    REP(i,e[a].size()){
        int b=e[a][i];
        if (b!=p){type[b]=type[a]; dfsb(b,a); A[a]+=A[b];}
    }
    REP(i,e[a].size()){
        int b=e[a][i];
        if (b!=p) skip[b]=A[b]>(A[a]-1)/2?a:-2;
    }
}


void dfsc(int a, int c){
    if (c==-1) c=a;
    int fd=0;
    REP(i,e[a].size()){
        int b=e[a][i];
        if (b!=par[a]){
            if (skip[b]<0) dfsc(b,-1);
            else skip[b]=c, dfsc(b,c), fd=1;
        }
    }
    if (!fd && c!=a){
        rmp[c]=getseg();
        tbl[rmp[c]].init(d[c],d[a]);
    }
}


int query(int a, int b){
    int res=0;
    while(a!=b){
        if (skip[a]<0) res+=skip[a]+2, a=par[a];
        else{
            if (d[skip[a]]<d[b]) res+=tbl[rmp[skip[a]]].query(d[b],d[a]), a=b;
            else res+=tbl[rmp[skip[a]]].query(d[skip[a]], d[a]), a=skip[a];
        }
    }
    return res;
}

void update(int a, int b){
    while(a!=b){
        if (skip[a]<0) skip[a]=-3-skip[a], a=par[a];
        else{
            if (d[skip[a]]<d[b]) tbl[rmp[skip[a]]].update(d[b],d[a]), a=b;
            else tbl[rmp[skip[a]]].update(d[skip[a]], d[a]), a=skip[a];
            
        }
    }
}


int lca(int a, int b){
    int last=-1;
    while(a!=b){
        if (d[a]>d[b]) swap(a,b);
        if (skip[b]<0) b=par[b], last=-1;
        else last=a, b=skip[b];
    }
    if (last==-1) return a;
    return last;
}

int main(){
    int m;
    cin>>n>>m;
    REP(i,n){ int a, b; scanf("%d %d", &a,&b); --a; --b; e[a].pb(b); e[b].pb(a); }
    dfs(0,-1);
    memset(type,-1,sizeof(type));
    REP(i,cycle.size()-1){
        int a=cycle[i], b=cycle[i+1];
        type[a]=a;

        REP(i,e[a].size()) if (e[a][i]==b) swap(e[a][i], e[a].back()), e[a].pop_back();
        swap(a,b);
        REP(i,e[a].size()) if (e[a][i]==b) swap(e[a][i], e[a].back()), e[a].pop_back();
    }

    pos=0;
    int na=cycle.size()-1;
    REP(i,na) dfsb(cycle[i],-1), dfsc(cycle[i],-1), cyclePos[cycle[i]]=i;
    

    segTree &ctree=tbl[getseg()];

    ctree.init(0,na);
    int res=n;
    REP(q,m){
        int a, b; scanf("%d %d", &a,&b); --a; --b;
        if (type[a]==type[b]){
            int c=lca(a,b);
            assert(d[c]<=d[a]);
            assert(d[c]<=d[b]);
            res+=query(a,c)+query(b,c);
            update(a,c); update(b,c);
            res-=query(a,c)+query(b,c);

        }else{
            res+=query(a,type[a])+query(b,type[b]);
            update(a,type[a]); update(b,type[b]);
            res-=query(a,type[a])+query(b,type[b]);

            //now update on cycle
            a=cyclePos[type[a]]; b=cyclePos[type[b]];
            if (a<b) a+=na;
            int u=cycle[(a+1)%na], v=cycle[(na+a-1)%na];
            int da=(na+b-a)%na, db=(na+a-b)%na;


            if (ctree.query(0,na)==na) --res;
            if (da<db || (da==db && u<v)){
                if (a%na<b){
                    res+=ctree.query(a%na,b);
                    ctree.update(a%na,b);
                    res-=ctree.query(a%na,b);
                }else{
                    res+=ctree.query(a%na,na);
                    ctree.update(a%na,na);
                    res-=ctree.query(a%na,na);

                    res+=ctree.query(0,b);
                    ctree.update(0,b);
                    res-=ctree.query(0,b);
                }
            }else{
                if (a%na>b){
                    res+=ctree.query(b,a%na);
                    ctree.update(b,a%na);
                    res-=ctree.query(b,a%na);
                }else{
                    res+=ctree.query(0,a%na);
                    ctree.update(0,a%na);
                    res-=ctree.query(0,a%na);

                    res+=ctree.query(b,na);
                    ctree.update(b,na);
                    res-=ctree.query(b,na);
                }
            }
            if (ctree.query(0,na)==na) ++res;
        }

        printf("%d\n", res);
    }
    return 0;
}



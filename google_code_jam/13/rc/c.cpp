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

const int oo=1e9;
const int maxb=22;
const int maxn=1111;
const int maxt=1e6;

int n;
vi lst[maxt];
int nx;

int xl[maxn*maxn*2];
int pos;

struct node;
node *getn();

struct node{
    int t,h;
    node *l,*r;
    int v;
    int v2;



    void init(int a, int b){
        t=a; h=b;
        v=0;
        if (t+1==h) return;
        int m=a+b>>1;
        l=getn(); r=getn();
        l->init(a,m);
        r->init(m,b);
    }

    int query(int a, int b){
        if (a>=h || b<=t) return oo;
        if (a<=t && h<=b) return getv();
        int u=min(l->query(a,b),r->query(a,b));
        return max(u,v2);
    }

    void update(int a, int b, int x){
        if (a>=h || b<=t) return; 
        if (a<=t && h<=b){
            v2=max(v2,x);
            return;
        }

        l->update(a,b,x);
        r->update(a,b,x);
        v=min(l->getv(),r->getv());
    }
    int getv(){return max(v,v2);}


}A[1<<maxb];

node *getn(){return A+pos++;}


struct data{
    int n;
    int x1,x2,dx;
    int s,ds;
    int dt;
    void read(){
        scanf(" %d%d%d",&n,&x1,&x2);
        scanf(" %d%d%d%d",&s,&dt,&dx,&ds);
    }

    void finish(int t, int i){
        update2();
        --n;
        x1+=dx; x2+=dx;
        s+=ds;
        if (n) lst[t+dt].pb(i);
    }

    int proc(){
        int xa=lower_bound(xl,xl+nx,x1)-xl;
        int xb=lower_bound(xl,xl+nx,x2)-xl;
        return A[0].query(xa,xb)<s;
    }

    void update2(){
        int xa=lower_bound(xl,xl+nx,x1)-xl;
        int xb=lower_bound(xl,xl+nx,x2)-xl;
        A[0].update(xa,xb,s);
    }

    void addxl(){
        int x=x1;
        REP(i,n) xl[nx++]=x, x+=dx;
        x=x2;
        REP(i,n) xl[nx++]=x, x+=dx;
    }

}tb[maxn];

int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        cin>>n;
        memset(A,0,sizeof(A));

        nx=0;
        REP(i,n){
            int t0;
            scanf(" %d",&t0);
            lst[t0].pb(i);
            tb[i].read();
            tb[i].addxl();
        }
        xl[nx++]=INT_MIN;
        sort(xl,xl+nx);
        nx=unique(xl,xl+nx)-xl;

        pos=1;
        A[0].init(0,nx);

        int res=0;
        REP(i,maxt) if (lst[i].size()){
            REP(j,lst[i].size()) res+=tb[lst[i][j]].proc();
            REP(j,lst[i].size()) tb[lst[i][j]].finish(i,lst[i][j]);
            lst[i].clear();
        }

        printf("Case #%d: ",ti+1);
        cout<<res<<endl;
    }
    return 0;
}


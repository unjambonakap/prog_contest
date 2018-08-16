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

struct data{
    int a,b,c;
    data(int a, int b, int c):a(a),b(b),c(c){}
    bool operator<(const data &d)const{return c>d.c;}
};

const int maxn=255;
const int oo=1e9;
int Y;
int x[maxn], y[maxn];
ll d[maxn][maxn];
ll r[maxn], c[maxn];
int xx[maxn][maxn];
int n,m;
int best[maxn][maxn][maxn];

int cx[maxn][maxn];
priority_queue<data> q;


void add(int a, int b, int c){ if (cx[a][b]>c){ q.push(data(a,b,cx[a][b]=c)); } }


void go(){
    while(q.size()) q.pop();
    q.push(data(n-2,0,c[0]));

    memset(cx,0x7f,sizeof(cx));
    cx[n-2][0]=c[0];

    while(q.size()){
        data xx=q.top(); q.pop();
        int a=xx.a, b=xx.b, cc=xx.c;
        if (a>=n-2 && b) continue;
        if (cx[a][b]<cc) continue;

        if (b!=m-1) add(a,b+1,cc-c[b]+c[b+1]);

        if (a==n-1){ printf("%d\n",cc); return; }
        REP(j,n) if (j!=a){
            int nb=best[a][j][b];
            if (nb!=m) add(j,nb,cc+c[nb]);
        }
    }
    puts("impossible");
}



ll dist(int a, int b){return 1ll*a*a+1ll*b*b;}

int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        cin>>n>>m>>Y;
        REP(i,n) scanf(" %d%d",x+i,y+i);

        REP(i,n) REP(j,n) d[i][j]=dist(x[i]-x[j],y[i]-y[j]);
        REP(i,n) d[i][n]=d[n][i]=dist(y[i],0), d[i][n+1]=d[n+1][i]=dist(y[i]-Y,0);
        d[n][n+1]=d[n+1][n]=1ll*Y*Y;
        n+=2;


        vector<pii> tb(m);
        REP(i,m) scanf(" %d%d",&tb[i].ND,&tb[i].ST);

        sort(ALL(tb));
        m=1;
        REP(i,tb.size()) if (tb[i].ND>r[m-1]) r[m]=tb[i].ND, c[m]=tb[i].ST, ++m;

        REP(i,n) REP(j,n){
            int pos=m;
            REP(k,m){
                while(pos>0 && d[i][j]<=dist(r[pos-1]+r[k],0)) --pos;
                best[i][j][k]=pos;
            }
        }
        
        go();
    }
    return 0;
}


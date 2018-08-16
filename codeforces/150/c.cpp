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

const int maxn=2222;
const int oo=2e9;
vi xl,yl;

int vx[]={0,0,1,-1};
int vy[]={1,-1,0,0};

int dir[maxn], l[maxn];
int n;
int N;
int sx[maxn], sy[maxn];
int rx[maxn], ry[maxn];

char rmp[222];
int grid[maxn][maxn];
int vis[maxn][maxn];

int qx[maxn*maxn], qy[maxn*maxn];
int na,ne;

int in(int a, int b){return a>=0&&b>=0&&a<maxn&&b<maxn;}

void bfs(){

    na=ne=0;
    qx[0]=qy[0]=0; ++ne;
    vis[0][0]=1;
    while(na<ne){
        int a=qx[na], b=qy[na++];
        grid[a][b]=0;
        REP(k,4){
            int x=a+vx[k], y=b+vy[k];
            if (in(x,y) && !vis[x][y]) vis[x][y]=1, qx[ne]=x, qy[ne]=y, ++ne;
        }
    }
}


int main(){
    cin>>N;
    rmp['U']=0;
    rmp['D']=1;
    rmp['L']=2;
    rmp['R']=3;


    int x=0, y=0;
    REP(i,N){
        char buf[10];
        scanf("%s %d",buf,l+i);
        dir[i]=rmp[buf[0]];

        xl.pb(x); yl.pb(y);
        x+=vx[dir[i]]*l[i];
        y+=vy[dir[i]]*l[i];
    }
    xl.pb(x); yl.pb(y);

    sort(ALL(xl));
    sort(ALL(yl));
    xl.resize(unique(ALL(xl))-xl.begin());
    yl.resize(unique(ALL(yl))-yl.begin());
    xl.pb(oo); yl.pb(oo);

    int nx=0, ny=0;
    REP(i,xl.size()-1){
        rx[i]=nx;
        sx[nx++]=1;
        if (xl[i+1]!=xl[i]+1) sx[nx++]=xl[i+1]-xl[i]-1;
    }

    REP(i,yl.size()-1){
        ry[i]=ny;
        sy[ny++]=1;
        if (yl[i+1]!=yl[i]+1) sy[ny++]=yl[i+1]-yl[i]-1;
    }

    REP(i,maxn) REP(j,maxn) grid[i][j]=1;
    x=0, y=0;
    REP(i,N){
        int xa=lower_bound(ALL(xl),x)-xl.begin();
        int ya=lower_bound(ALL(yl),y)-yl.begin();
        xa=rx[xa]; ya=ry[ya];

        x+=vx[dir[i]]*l[i];
        y+=vy[dir[i]]*l[i];
        int xb=lower_bound(ALL(xl),x)-xl.begin();
        int yb=lower_bound(ALL(yl),y)-yl.begin();
        xb=rx[xb]; yb=ry[yb];

        if (xa!=xb){
            if (xa>xb) swap(xa,xb);
            for (; xa<=xb; ++xa) vis[1+xa][1+ya]=1;
        }else{
            if (ya>yb) swap(ya,yb);
            for (; ya<=yb; ++ya) vis[1+xa][1+ya]=1;
        }
    }

    bfs();

    ll res=0;
    REP(i,nx) REP(j,ny) res+=1ll*grid[i+1][j+1]*sx[i]*sy[j];
    cout<<res<<endl;



    return 0;
}


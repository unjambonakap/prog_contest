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
#define FOR(i, a, b) for(int i = (int)(a); i <= (int)(b); ++i)
#define FORV(i, a, b) for(int i = (int)(a); i >= (int)(b); --i)

#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();++i)
#define FEV(i,t) for (typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();++i)

#define SZ(a) (int((a).size()))
#define two(x) (1 << (x))
#define twoll(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()
#define CLR(a) (a).clear()


#define pb push_back
#define PF push_front
#define ST first
#define ND second
#define MP(x,y) make_pair(x, y)

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef queue<int> qi;

template<class T> void checkmin(T &a, T b){if (b<a)a=b;}
template<class T> void checkmax(T &a, T b){if (b>a)a=b;}
template<class T> void out(T t[], int n){REP(i, n)cout<<t[i]<<" "; cout<<endl;}
template<class T> void out(vector<T> t, int n=-1){for (int i=0; i<(n==-1?t.size():n); ++i) cout<<t[i]<<" "; cout<<endl;}
inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:(n&1?0:ctz(n>>1)+1));}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int maxn=100;
int n, m;
char mb[maxn][maxn];
char ma[maxn][maxn];
char degb[maxn][maxn];


struct diag{
    int x, y, r;
    int vx, vy;
    diag(int x, int y, int vx, int vy, int r):x(x), y(y), vx(vx), vy(vy), r(r){ 
        //printf("%d %d %d %d\n", y, x, vy, vx);
    }
};
int tmp[]={0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1};


int parent[maxn*maxn];
int root(int a){return (parent[a]==-1?a:parent[a]=root(parent[a]));}

int checkit(){
    memset(parent, -1, sizeof(parent));
    int cnt=n*m;
    REP(i, n-1) if (mb[0][i]==mb[0][i+1]) --degb[0][i], --degb[0][i+1], parent[root(i+1)]=root(i), --cnt;
    
    FOR(i, 1, m-1) REP(j, n){
        int nv;
        if (degb[i-1][j]==0) nv=mb[i-1][j]^1;
        else if (degb[i-1][j]==1){
            parent[root(i*n+j)]=root((i-1)*n+j);
            --cnt;
            nv=mb[i-1][j], --degb[i][j];
        }else return 0;
        if (j && nv==mb[i][j-1]){
            if (root(i*n+j)!=root(i*n+j-1)) parent[root(i*n+j-1)]=root(i*n+j), --cnt;
            --degb[i][j], --degb[i][j-1];
        }
        if (mb[i][j]!=-1 && mb[i][j]!=nv) return 0;
        mb[i][j]=nv;
    }
    REP(j, n) if (degb[m-1][j]!=0) return 0;

    //if (cnt==2){
    //    REP(i, m) REP(j, n) if (mb[i][j]!=tmp[i*n+j]) return 0;
    //    REP(i, m){REP(j, n) printf("%d ", mb[i][j]);printf("\n");}
    //    printf("\n");
    //}
    return cnt==2;
}


int in(int a, int b){return a>=0 && b>=0 && a<n && b<m;}
int intersect(const diag &a, const diag &b, int &x, int &y){
    x=a.x; y=a.y;
    if (a.vx*b.vy-a.vy*b.vx==0) return -1;
    if (x==b.x && y==b.y) return a.r;
    int k;
    int e, f;
    e=(a.x-b.x)/b.vx*b.vy;
    f=a.vx/b.vx*b.vy;
    e=b.y-a.y+e;
    f=a.vy-f;

    k=e/f;
    if (e%f!=0) return -1;


    x+=a.vx*k;
    y+=a.vy*k;
    assert(fabs(x-b.x)==fabs(y-b.y));
    int ka=fabs(x-b.x);

    int r=a.r^(k&1);
    if (!in(x, y)) return -1;
    if (r==(b.r^(ka&1))) return r;
    return -1;
}


ll solve(){
    int na=2*(n+m)-4;
    pii rmp[na+1];
    int p=0;
    rmp[p++]=MP(0, 1);
    REP(i, n) rmp[p++]=MP(i, 0);
    REP(i, m-2) rmp[p++]=MP(n-1, i+1);
    REPV(i, n) rmp[p++]=MP(i, m-1);
    REPV(i, m-2) rmp[p++]=MP(0, i+1);

    ll res=0;
    FOR(i, 1, na-1) FOR(j, 1, i){
        vector<pii> ta, tb;

        memset(ma, -1, sizeof(ma));
        FOR(k, 1, na) ma[rmp[k].ND][rmp[k].ST]=(k<=i&&k>=j);

        vector<diag> vd;
        vd.pb(diag(0, 0, 1, 1, ma[0][0]));
        vd.pb(diag(n-1, m-1, -1, -1, ma[m-1][n-1]));
        vd.pb(diag(0, m-1, 1, -1, ma[m-1][0]));
        vd.pb(diag(n-1, 0, -1, 1, ma[0][n-1]));

        int nx, ny;
        nx=rmp[j-1].ST-rmp[j].ST; ny=rmp[j-1].ND-rmp[j].ND;
        if (!nx) nx=rmp[j].ST?-1:1;
        if (!ny) ny=rmp[j].ND?-1:1;
        vd.pb(diag(rmp[j-1].ST, rmp[j-1].ND, nx, ny, 0));


        nx=rmp[j-1].ST-rmp[j].ST; ny=rmp[j-1].ND-rmp[j].ND;
        nx=-nx; ny=-ny;
        if (!nx) nx=rmp[j].ST?-1:1;
        if (!ny) ny=rmp[j].ND?-1:1;
        vd.pb(diag(rmp[j].ST, rmp[j].ND, nx, ny, 1));

        nx=rmp[i].ST-rmp[i+1].ST; ny=rmp[i].ND-rmp[i+1].ND;
        if (!nx) nx=rmp[i].ST?-1:1;
        if (!ny) ny=rmp[i].ND?-1:1;
        vd.pb(diag(rmp[i].ST, rmp[i].ND, nx, ny, 1));


        nx=rmp[i].ST-rmp[i+1].ST; ny=rmp[i].ND-rmp[i+1].ND;
        nx=-nx; ny=-ny;
        if (!nx) nx=rmp[i].ST?-1:1;
        if (!ny) ny=rmp[i].ND?-1:1;
        vd.pb(diag(rmp[i+1].ST, rmp[i+1].ND, nx, ny, 0));

        REP(_i, vd.size()) REP(_j, _i){
            int x, y, r;
            r=intersect(vd[_i], vd[_j], x, y);
            if (r==1 && ma[y][x]!=0) ta.pb(MP(y, x));
            if (r==0 && ma[y][x]!=1) tb.pb(MP(y, x));
        }


        sort(ALL(ta)); sort(ALL(tb));
        ta.resize(unique(ALL(ta))-ta.begin());
        tb.resize(unique(ALL(tb))-tb.begin());
        int na=ta.size(), nb=tb.size();

        //printf("%d %dxxx\n", na, nb);
        //REP(_i, na) printf("%d %d\n", ta[_i].ND, ta[_i].ST);
        //REP(_i, nb) printf("%d %d\n", tb[_i].ND, tb[_i].ST);
        REP(ia, na) REP(ja, ia) REP(ib, nb) REP(jb, ib){

            memcpy(mb, ma, sizeof(ma));
            memset(degb, 2, sizeof(degb));
            mb[ta[ia].ST][ta[ia].ND]=mb[ta[ja].ST][ta[ja].ND]=1;
            mb[tb[ib].ST][tb[ib].ND]=mb[tb[jb].ST][tb[jb].ND]=0;
            degb[ta[ia].ST][ta[ia].ND]=degb[ta[ja].ST][ta[ja].ND]=1;
            degb[tb[ib].ST][tb[ib].ND]=degb[tb[jb].ST][tb[jb].ND]=1;
            res+=checkit();
        }

    }

    return res*2;


}

int main(){
    int tn;
    cin>>tn;
    FOR(ti, 1, tn){
        cin>>n>>m;

        ll res=solve();
        printf("Case #%d: %Ld\n", ti, res);
    }

    return 0;
}



